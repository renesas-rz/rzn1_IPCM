
#include "SensorCollectorTask.hpp"
#include "kernel.h"
#include "kernel_id.h"

SensorCollectorTask::SensorCollectorTask(
    size_t max_buffer_count,
    GFCValve* sample_valve) :
  ASBRTTask<void*, SensorCollectorTask>(ASBRTTaskConfig("Sensor Collector"),
                                        SensorCollectorTask::collect_sensor_data),
  adc_sample_mask(0),
  max_buffer_count(max_buffer_count),
  sample_valve(sample_valve),
  data_buffering_progress(NULL),
  data_buffering_limit(NULL),
  active_buffers(NULL)
{
  config.task_priority = SENSOR_COLLECTOR_PRIO;
}


int SensorCollectorTask::init_task(DataChannel* channel_array, size_t count)
{
  unsigned int buffer_index, channel_index, max_buffer_index = 0;
  //TASK_OUTPUT("SensorCollectorTask::init_task() "\
              "Filling data_channels[%u]\r\n", count);
  for(size_t idx = 0; idx < count; idx++)
  {
    channel_index = mask_to_channel_index(channel_array[idx].mask);
    data_channels[channel_index] = channel_array[idx];
    max_buffer_index += channel_array[idx].mux_config->channel_count;
  }

  active_buffers = new DataBuffer::WritablePoolElement*[max_buffer_index];
  data_buffering_progress = new int[max_buffer_index];
  data_buffering_limit = new int[max_buffer_index];

  for(size_t idx = 0; idx < count; idx++)
  {
    channel_index = mask_to_channel_index(channel_array[idx].mask);
    const DataChannel& channel = data_channels[channel_index];
    //TASK_OUTPUT("SensorCollectorTask::init_task() "\
                "initiailzing for idx %u\r\n", idx);
    for(size_t mux_idx = 0; mux_idx < channel.mux_config->channel_count; mux_idx++)
    {
      //TASK_OUTPUT("SensorCollectorTask::init_task() "\
      //            "initiailzing for mux_idx %u\r\n", mux_idx);
      buffer_index = mask_and_mux_to_buffer_idx(channel.mask, mux_idx);
      //TASK_OUTPUT("SensorCollectorTask::init_task() "\
      //            "Computed buffer_index %u for idx(%u) mux_idx(%u)\r\n", buffer_index, idx, mux_idx);
      data_buffering_progress[buffer_index] = 0;
      data_buffering_limit[buffer_index] = channel.buffer_count;
      adc_sample_mask |= channel.mask;
      active_buffers[buffer_index] = NULL;
    }
  }
  buffer_pool.allocate(MAX_BUFFER_COUNT, BUFFER_POOL_CAPACITY);
  return ASBRTTask<void*, SensorCollectorTask>::init_task();
}

void SensorCollectorTask::collect_sensor_data(SensorCollectorTask* instance)
{
  GFCValveData valve_data;
  RawSensorDataOutput output;
  int rc, test_mask, channel_index, buffer_index;
  unsigned long mask_out = 0;

  if((rc = instance->setup_data_event()) < 0)
  {
    TASK_ERROR("SensorCollectorTask::collect_sensor_data() "\
               "encountered an error while setting up event: %d\r\n", rc);
  }

  while(1)
  {

    if((rc = instance->wait_for_data(mask_out, valve_data)))
    {
      TASK_ERROR("SensorCollectorTask::collect_sensor_data() "\
                 "encountered an error waiting for data: %d\r\n", rc);
    }
    for(test_mask = 0x1, channel_index = 0; test_mask != 0; test_mask <<= 1, channel_index++)
    {
      // ignore channels not configured for transmission, even if irq bit is set
      if(instance->data_channels[channel_index].channel_id != Invalid && (mask_out & test_mask))
      {
        // also populates the values within output
        if((rc = instance->handle_raw_data(test_mask, valve_data, output)))
        {
          TASK_ERROR("SensorCollectorTask::collect_sensor_data() "\
                     "encountered an error while handling raw data: %d\r\n", rc);
        }
        // mux index determined and filled in handle_raw_data()
        buffer_index = instance->mask_and_mux_to_buffer_idx(test_mask, output.mux_channel_index);

        if((rc = instance->handle_buffered_data(channel_index, buffer_index, output)))
        {
          TASK_ERROR("SensorCollectorTask::collect_sensor_data() "\
                     "encountered an error while handling buffered data: %d\r\n", rc);
        }
      }
    }
  }
}

int SensorCollectorTask::setup_data_event()
{
  return (int)clr_flg(ID_FLG_ADC_IRQ, 0x0);
}

int SensorCollectorTask::wait_for_data(
  unsigned long& mask_out, GFCValveData& valve_data)
{
  ER hwos_err;
  int rc;
  FLGPTN wait_ptn = 0xFFFF;

  if((hwos_err = wai_flg(ID_FLG_ADC_IRQ, wait_ptn, TWF_ORW, (FLGPTN*)&mask_out)) != E_OK)
  {
    return (int)hwos_err;
  }
  if((hwos_err = clr_flg(ID_FLG_ADC_IRQ, (FLGPTN)~mask_out)) != E_OK)
  {
    return hwos_err;
  }

  if((rc = sample_valve->readValveData(mask_out, &valve_data)))
  {
    TASK_ERROR("SensorCollectorTask::wait_for_data() "\
                "encountered an error while reading valve data: %d\r\n", rc);
    return rc;
  }

  return 0;
}

int SensorCollectorTask::handle_raw_data(
  int channel_mask, GFCValveData& new_data, RawSensorDataOutput& output)
{
  int rc;
  if((rc = channel_id_to_data(channel_mask, output, new_data)))
  {
    TASK_ERROR("SensorCollectorTask::handle_raw_data() "\
               "encountered an error while converting data "\
               "for output mask %d: %d\r\n", channel_mask, rc);
    return rc;
  }

  // if there are no receivers, do not attempt to produce
  if(ASBRTProducer<RawSensorDataOutput>::receiver_count() == 0)
  {
    return 0;
  }
  if((rc = ASBRTProducer<RawSensorDataOutput>::produce(output)))
  {
    TASK_ERROR("SensorCollectorTask::handle_raw_data() "\
               "encountered an error while producing on "\
               "raw data channel: %d\r\n", rc);
    return rc;
  }
  return 0;
}


int SensorCollectorTask::handle_buffered_data(
    int channel_index, int buffer_index, RawSensorDataOutput& new_data)
{
  BufferedSensorDataOutput buffered_output;
  int rc;
  int buffer_limit = data_buffering_limit[buffer_index];
  // if this channel is not in use, ignore it
  if(buffer_limit < 0)
  {
    TASK_ERROR("SensorCollectorTask::handle_buffered_data() "\
               "encountered a buffer index %d that is not in use\r\n",
               buffer_index);
    return -1;
  }
  int& buffer_progress = data_buffering_progress[buffer_index];
  int receiver_count = ASBRTProducer<RawSensorDataOutput>::receiver_count();
  DataBuffer::WritablePoolElement* active_buffer = active_buffers[buffer_index];
  if(active_buffer == NULL)
  {
    // since connections are all before tasks starting, the ref count won't change later
    if(!(active_buffer = buffer_pool.acquire(receiver_count)))
    {
      TASK_ERROR("SensorCollectorTask::handle_buffered_data() "\
                 "got a NULL buffer element for channel %d\r\n",
                 channel_index);
      return 1;
    }
    active_buffers[buffer_index] = active_buffer;
  }
  (*active_buffer)[buffer_progress++] = new_data.data;
  if(buffer_progress >= buffer_limit)
  {
    const SensorCollectorTask::DataChannel& channel = data_channels[channel_index];
    buffered_output.channel_id = channel.channel_id;
    buffered_output.buffer_length = channel.buffer_count;
    buffered_output.data = active_buffer;
    buffered_output.mux_index = new_data.mux_channel_index;
    // only produce if there is a receiver listening
    if(receiver_count > 0 &&
       (rc = ASBRTProducer<BufferedSensorDataOutput>::produce(buffered_output)))
    {
      TASK_ERROR("SensorCollectorTask::handle_buffered_data() "\
                 "encountered an error while trying to produce "\
                 "on channel %d: %d\r\n",
                 channel_index, rc);
      return rc;
    }
    // get new buffer for later use
    active_buffers[buffer_index] = buffer_pool.acquire(receiver_count);
    buffer_progress = 0;
  }
  return 0;
}

int SensorCollectorTask::mask_and_mux_to_buffer_idx(
  unsigned long mask, unsigned long mux_idx)
{
  int index = 0, channel_idx = 0;
  while(mask >>= 0x1)
  {
    // an Invalid channel_id (default) indicates the mask is not in use
    if(data_channels[channel_idx].channel_id == Invalid)
    {
      continue;
    }
    // for each index, add the number of mux channels to the total
    index += data_channels[channel_idx++].mux_config->channel_count;
  }
  // offset by mux index
  index += mux_idx;
  return index;
}

// this method converts the bitmask (1,2,4,8) to the index (0,1,2,3)
int SensorCollectorTask::mask_to_channel_index(unsigned long mask)
{
  int channel_idx = 0;
  while(mask >>= 0x1)
  {
    channel_idx++;
  }
  return channel_idx;
}

int SensorCollectorTask::channel_id_to_data(
    int channel_mask, RawSensorDataOutput& output, GFCValveData& data)
{
  // don't know which mux to use at this point, so get channel id of base index
  int channel_index = mask_to_channel_index(channel_mask);
  /* TASK_OUTPUT("SensorCollectorTask::channel_id_to_data() " \
               "found a channel_index of %d for channel_mask %d and mux_idx 0\n",
               channel_index, channel_mask);*/
  output.channel_id = data_channels[channel_index].channel_id;
  /* TASK_OUTPUT("SensorCollectorTask::channel_id_to_data() " \
               "found a channel_id of %d for channel_index %d\n",
               output.channel_id, channel_index);*/
  switch(output.channel_id)
  {
  case CapSensor:
    output.mux_channel_index = data.capSensorValue.mux_channel;
    output.data = data.capSensorValue.sample;
    break;
  case DownstreamPressureSensor:
    output.mux_channel_index = data.down_pressure.mux_channel;
    output.data = data.down_pressure.sample;
    break;
  case UpstreamPressureSensor:
    output.mux_channel_index = data.up_pressure.mux_channel;
    output.data = data.up_pressure.sample;
    break;
  case TemperatureSensor:
    output.mux_channel_index = data.temperatureSensorValue.mux_channel;
    output.data = data.temperatureSensorValue.sample;
    break;
  case Invalid:
  default:
    return 1;
  }
  return 0;
}
