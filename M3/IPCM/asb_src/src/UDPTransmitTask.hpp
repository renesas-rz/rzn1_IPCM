
/**
 * \ingroup task_instance
 * @brief Definition of the UDPTransmitTask class
 * 
 * This task transmits buffered data along a different UDP port for each data
 * channel.
 * 
 * @file UDPTransmitTask.hpp
 * @author your name
 * @date 2018-03-23
 */

#ifndef _UDP_TRANSMIT_TASK_H
#define _UDP_TRANSMIT_TASK_H

#include "ASBRTTask.hpp"
#include "TaskMessages.hpp"
#include "lwip/sockets.h"

/**
 * \ingroup task_instance
 * @brief The UDPTransmitTask outputs buffered sensor data on the network
 * 
 * The UDPTransmitTask output \ref ASBNetworkOutput formatted data over the
 * network on a set of preconfigured UDP ports. Each data channel is sent
 * out on a different port.
 * 
 */
class UDPTransmitTask : 
  public ASBRTTask<void*, UDPTransmitTask>,
  public ASBRTQueuedReceiver<BufferedSensorDataOutput>
{
public:
  /**
   * @brief Construct a new UDPTransmitTask object
   * 
   */
  UDPTransmitTask();

  /**
   * @brief A specification type for output channels
   * 
   */
  struct OutputChannelSpec
  {
    /**
     * @brief Construct a new Output Channel Spec object
     * 
     */
    OutputChannelSpec() : 
      channel_id(-1), mux_index(1), transmitter_address(NULL), 
      receiver_address(NULL), udp_port(-1), sample_period(0)
    {

    }
    /// the output channel ID; should correspond with \ref SensorChannelID
    int channel_id;
    /// the sub-index used for multiplexing this channel specifies
    unsigned int mux_index;
    /// the network IP to send messages as
    const char* transmitter_address;
    /// the IP address to send collected data to
    const char* receiver_address;
    /// the udp port on which the data should be sent
    int udp_port;
    /// the number of microseconds each sample represents
    unsigned int sample_period;
  };

  /**
   * @brief initializes this transmit task to implement the given set of 
   * output channels
   * 
   * @param spec_array the output channel specification array
   * @param spec_count the number of output specs in the given array
   * @return int 0 on success, an error code otherwise
   */
  int init_task(OutputChannelSpec* spec_array, size_t spec_count);

  /**
   * @brief Get the transmission address as a string
   * 
   * @param stream_idx the index to get the address of
   * @return std::string a human readable transmission address
   */
  std::string get_transmission_address(int stream_idx);

private:
  /**
   * @brief the primary task function for UDPTransmitTask instances
   * 
   * This function retrieves buffered sensor data and formats it for output
   * to the configured network devices as its main loop.
   * 
   * @param instance of the task this function will work off of
   */
  static void transmit_udp_data(UDPTransmitTask* instance);

  /**
   * @brief formats buffered sensor data and transmits it on network
   * 
   * @param new_data the data to parse and transmit
   * @return int 0 on success, an error code otherwise
   */
  int send_new_data(BufferedSensorDataOutput& new_data);

  /**
   * @brief determines the broadcast address for the given network interface
   * and outputs it into the given address struct
   * 
   * @param target_if the name of the network interface to find the address of
   * @param addr a pointer to a sockaddr_in instance to output on
   * @return int 0 on success, an error code otherwise
   */
  static int determine_broadcast_addr(
    const char* target_if, struct sockaddr_in* addr);

  /**
   * @brief determines which spec this channel/ mux combo refers to
   * 
   */
  size_t get_tranmission_spec(
    SensorChannelID channel_id, unsigned int mux_index);

  /// the fd of the socket to transmit on
  int transmit_socket;
  /// an array of network addresses to transmit on for each data channel
  struct sockaddr_in* output_addr_arr;
  /// the number of channels in use
  size_t stream_count;
  /// a running message counter
  unsigned long* message_counter_arr;
  /// the sample period of each channel
  long* sample_period_array;
  /// the highest mux index in use
  unsigned int channel_id_max_mux[SensorChannelsCount];
  /// a 2D array that maps channel id and mux index to stream index
  int* channel_mux_to_stream_index[SensorChannelsCount];
};

#endif
