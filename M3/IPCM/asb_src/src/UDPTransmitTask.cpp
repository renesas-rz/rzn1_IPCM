
#include "UDPTransmitTask.hpp"

#include "UDPCollector.hpp"
//#include <sstream>
//#include <string>

UDPTransmitTask::UDPTransmitTask() :
  ASBRTTask<void*, UDPTransmitTask>(
    ASBRTTaskConfig("UDPTransmitTask"),
    UDPTransmitTask::transmit_udp_data),
  ASBRTQueuedReceiver<BufferedSensorDataOutput>("buffered queue", 64),
  transmit_socket(0),
  stream_count(0)
{
  config.task_priority = UDP_TX_PRIO;
}


int UDPTransmitTask::init_task(OutputChannelSpec* spec_array, size_t spec_count)
{
  int option_val = 1;
  unsigned int mux_index, channel_id;
  stream_count = spec_count;
  memset(channel_id_max_mux, '\0', sizeof(int) * SensorChannelsCount);

  // create transmission socket and configure
  if((transmit_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    transmit_socket = 0;
    return errno;
  }
  if(setsockopt(
    transmit_socket, SOL_SOCKET, SO_BROADCAST, &option_val, sizeof(int)))
  {
    return errno;
  }

  // allocate runtime arrays
  output_addr_arr = new sockaddr_in[stream_count];
  message_counter_arr = new unsigned long[stream_count];
  sample_period_array = new long[stream_count];

  // determine mux channels per channel id
  for(size_t spec_idx = 0; spec_idx < spec_count; spec_idx++)
  {
    const OutputChannelSpec& spec = spec_array[spec_idx];
    mux_index = spec.mux_index;
    channel_id = spec.channel_id;
    if(mux_index > channel_id_max_mux[channel_id])
    {
      channel_id_max_mux[channel_id] = mux_index;
    }
  }

  // allocated mapping sub-arrays
  for(size_t channel_id = 0; channel_id < SensorChannelsCount; channel_id++)
  {
    size_t sub_array_size = channel_id_max_mux[channel_id] + 1;
    channel_mux_to_stream_index[channel_id] = new int[sub_array_size];
    // fill with -1 initially so gaps can be detected later
    for(unsigned int i = 0; i < sub_array_size; i++)
    {
      channel_mux_to_stream_index[channel_id][i] = -1;
    }
  }

  // populate address and counter arrays
  for(size_t spec_idx = 0; spec_idx < spec_count; spec_idx++)
  {
    const OutputChannelSpec& spec = spec_array[spec_idx];
    struct sockaddr_in& addr = output_addr_arr[spec_idx];
    addr.sin_port = htons(spec.udp_port);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(spec.receiver_address);
    message_counter_arr[spec_idx] = 0;
    sample_period_array[spec_idx] = spec.sample_period;
    channel_mux_to_stream_index[spec.channel_id][spec.mux_index] = spec_idx;
  }
  return ASBRTTask<void*, UDPTransmitTask>::init_task();
}

#ifdef AAA
std::string UDPTransmitTask::get_transmission_address(int stream_idx)
{
  if(transmit_socket <= 0)
  {
    throw std::runtime_error(
      "Calling get_transmission_address() on an unitialized UDPTransmitTask");
  }
  if(stream_idx < 0 || stream_idx >= stream_count)
  {
    TASK_ERROR("UDPTransmitTask::get_transmission_address() "\
               "Got a stream_idx of %d when %d was max\n",
               stream_idx, stream_count);
    throw std::out_of_range("stream_idx is out of range");
  }
  const struct sockaddr_in& output_addr = output_addr_arr[stream_idx];
  char ip_buffer[64];
  if(!inet_ntop(AF_INET, (void*)&output_addr.sin_addr, &ip_buffer[0], 64))
  {
    throw std::runtime_error(
      "Unable to convert address to string in get_transmission_address()");
  }
  std::stringstream ss;
  ss << ip_buffer << ':' << ntohs(output_addr.sin_port);
  return ss.str();
}
#endif


void UDPTransmitTask::transmit_udp_data(UDPTransmitTask* instance)
{

  BufferedSensorDataOutput to_output;
  int rc;
  while(1)
  {
    if((rc = instance->retrieve(to_output)) < 0)
    {
      TASK_ERROR("UDPTransmitTask::transmit_udp_data() "\
                 "encountered an error retrieving data: %d\r\n", rc);
    }
    if((rc = instance->send_new_data(to_output)))
    {
      TASK_ERROR("UDPTransmitTask::transmit_udp_data() "\
                 "encountered an error sending data: %d\r\n", rc);
    }
  }
}

int UDPTransmitTask::send_new_data(BufferedSensorDataOutput& new_data)
{
  ASBNetworkOutput to_send;
  unsigned long channel_id, mux_index, sample_period, stream_index;
  channel_id = new_data.channel_id;
  // check that channel ID is in legal range
  if(channel_id < 0 || channel_id >= SensorChannelsCount)
  {
    TASK_ERROR("channel_id: %d\n", channel_id);
    throw std::out_of_range(
      "Got a buffered data sample with an illegal channel_id\r\n");
  }

  mux_index = new_data.mux_index;
  // check that mux index is in legal range
  if(mux_index > channel_id_max_mux[channel_id])
  {
    TASK_ERROR("mux_index: %d\r\n", mux_index);
    throw std::out_of_range(
      "Got a buffered data sample with an illegal mux_index");
  }
  stream_index = channel_mux_to_stream_index[channel_id][mux_index];

  // ignore unconfigured channels
  if(stream_index == -1)
  {
    new_data.data->release();
    return 0;
  }
  sample_period = sample_period_array[stream_index];

  if(sample_period < 0)
  {
    // drop samples that aren't configured for transmission
    return 0;
  }
  to_send.header.sample_id = channel_id;

  switch (to_send.header.sample_id)
  {
  case CapSensor:
    to_send.header.num_of_samples = ADC_CAP_BUFFERING;
    break;
  case UpstreamPressureSensor:
    to_send.header.num_of_samples = ADC_UP_PRESSURE_BUFFERING;
    break;
  case DownstreamPressureSensor:
    to_send.header.num_of_samples = ADC_DOWN_PRESSURE_BUFFERING;
    break;
  case TemperatureSensor:
    to_send.header.num_of_samples = ADC_TEMPERATURE_BUFFERING;
    break;
  }
  to_send.header.counter = message_counter_arr[stream_index]++;
  to_send.header.sample_duration = sample_period;
  to_send.header.mux_index = mux_index;
  size_t buf_length = new_data.buffer_length;
  new_data.data->copy_to(&to_send.data[0], buf_length);
  // release as soon as possible
  new_data.data->release();
  if(buf_length > MAX_BUFFER_COUNT)
  {
    throw std::runtime_error("Encountered buffered data with buffer size"\
                             "exceeding MAX_BUFFER_COUNT");
  }
  size_t send_size = sizeof(ASBNetworkHeader);
  send_size += sizeof(SensorDataType) * buf_length;
  const struct sockaddr_in& addr = output_addr_arr[stream_index];
  if(sendto(
    transmit_socket, (void*)&to_send, send_size, 0,
    (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
  {
    return errno;
  }
  return 0;
}
