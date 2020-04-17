
/**
 * \ingroup task_instance
 * @brief Definition of SensorCollectorTask class
 *
 * This task collects data from the physical sensors and outputs it both as a
 * raw data stream and a buffered data stream.
 *
 * @file SensorCollectorTask.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _SENSOR_COLLECTOR_TASK_H
#define _SENSOR_COLLECTOR_TASK_H

#include "ASBRTTask.hpp"
#include "GFCValve.hpp"
#include "ASBConfig.hpp"

/// Don't think this is going to change any time soon
#define BITS_PER_BYTE   8
/// number of bits contained in a Xenomai event bitmask
#define MASK_BIT_COUNT  (sizeof(unsigned long)*BITS_PER_BYTE)

/**
 * \ingroup task_instance
 * @brief The SensorCollectorTask collects data from a given GFCValve
 * instance and outputs it
 *
 * The SensorCollectorTask collects all available data from the given
 * GFCValve instance and outputs it on its raw and buffered data channels.
 * Each new sample of any ADC results in a new \ref RawSensorDataOutput
 * output while the data within a configured number of these points is
 * collected into a BufferedSensorDataOutput instance. This buffered output
 * contains a pointer to a \ref PoolElement that contains the buffered data
 * (thus avoiding excessive copying).
 *
 */
class SensorCollectorTask :
  public ASBRTTask<void*, SensorCollectorTask>,
  public ASBRTProducer<RawSensorDataOutput>,
  public ASBRTProducer<BufferedSensorDataOutput>
{
private:
  // utility functions
  /**
   * @brief converts a bitmask and a mux index to a stream index
   *
   * @param mask the mask to convert
   * @param mux_idx the mux index in question
   * @return int the index into the active streams for this combination
   */
  int mask_and_mux_to_buffer_idx(
    unsigned long mask, unsigned long mux_idx);

  /**
   * @brief converts a bitmask to a monotonic index
   *
   * @param mask the mask to convert
   * @return int the index of the most significant bit that is 1 base on its
   * its offset from the least significant bit.
   */
  static int mask_to_channel_index(unsigned long mask);

  /**
   * @brief returns the part of the data corresponding to the given bitmask
   * from within the given valve data instance.
   *
   * @param output the ouptut struct instance to fill
   * @param data a GFCValveData instance that contains the desired data
   * @return int 0 on success
   */
  int channel_id_to_data(
    int channel_mask, RawSensorDataOutput& output, GFCValveData& data);

public:
  /**
   * @brief Construct a new Sensor Collector Task object
   *
   * @param max_buffer_count the maximum allowed buffer count that may be
   * specified within a DataChannel for this instance.
   * @param sample_valve the valve instance to collect data from
   */
  SensorCollectorTask(size_t max_buffer_count,
                      GFCValve* sample_valve);


  /**
   * @brief A specification struct for each channel of data collection
   *
   */
  struct DataChannel
  {
    /**
     * @brief Construct a new Data Channel object
     *
     */
    DataChannel() :
      name(NULL), mask(0), buffer_count(-1), mux_config(NULL), channel_id(Invalid) {}

    /// the name of this channel
    const char* name;
    /// the bitmask that corresponds to data of this channel being available
    unsigned int mask;
    /// the sensor channel this specifies
    SensorChannelID channel_id;
    /// the mulxiplex index of this data channel
    const MuxConfig* mux_config;
    /// the number of samples to buffer for this channel before broadcasting
    int buffer_count;
    /// a static function to fill a DataChannel object based on a config code
    static int data_channel_of_code(
      SensorCollectorTask::DataChannel& out,
      char code,
      const ASBConfig& config)
    {
      if((out.channel_id = sensor_channel_of_code(code)) == Invalid)
      {
        return 1;
      }

      if((out.mux_config = channel_id_to_mux_config(out.channel_id)) == NULL)
      {
        return 1;
      }

      switch(out.channel_id)
      {
      case CapSensor:
        out.name = "Position Capacitor";
        out.mask = ADC_CAP_MASK;
        out.buffer_count = config.adc_capacitor_buffering;
        break;
      case UpstreamPressureSensor:
        out.name = "Upstream Pressure Transducer";
        out.mask = ADC_UP_PRESSURE_MASK;
        out.buffer_count = config.adc_up_pressure_buffering;
        break;
      case DownstreamPressureSensor:
        out.name = "Downstream Pressure Transducer";
        out.mask = ADC_DOWN_PRESSURE_MASK;
        out.buffer_count = config.adc_down_pressure_buffering;
        break;
      case TemperatureSensor:
        out.name = "Temperature Sensor";
        out.mask = ADC_TEMPERATURE_MASK;
        out.buffer_count = config.adc_temperature_buffering;
        break;
      default:
        return 1;
      }
      return 0;
    }
  };

  /**
   * @brief intializes this SensorCollectorTask for the given channels.
   *
   * @param channel_array a pointer to an array of channel specifications
   * of length count
   * @param count the length of channel_array
   * @return int 0 on success, an error code otherwise
   */
  int init_task(DataChannel* channel_array, size_t count);

private:
  /**
   * @brief the primary task function of this task that collects the data
   *
   * This task sets up a Xenomai event that listens for new ADC data. It then
   * enters a main loop that consists of:
   *
   *  - wait for new data to be available
   *  - iterate through each possible mask and check if data was taken
   *  - if so, broadcast this new raw data
   *  - add this new data to the buffer for that channel
   *  - if the buffer is full, broadcast the buffered data
   *
   */
  static void collect_sensor_data(SensorCollectorTask*);

  // main support functions
  /**
   * @brief Set the up data event for receiving interrupts
   *
   * @return int 0 on succes, and error code otherwise
   */
  int setup_data_event();

  /**
   * @brief waits for data to be available then outputs the result
   *
   * Which samples are available is indicated by the presence of a 1
   * at the corresponding location in the output bitmask.
   *
   * @param mask_out the bitmask to output on
   * @param valve_data the valve data reference to output on
   * @return int 0 on success, an error code otherwise
   */
  int wait_for_data(
    unsigned long& mask_out, GFCValveData& valve_data);
  /**
   * @brief handles new raw data by filling the given RawSensorData object
   * and broadcasting it
   *
   * @param channel_mask the mask of the channel to broadcast on
   * @param new_data the new data object
   * @param output the raw data reference to update
   * @return int 0 on success, an error code otherwise
   */
  int handle_raw_data(
    int channel_mask, GFCValveData& new_data, RawSensorDataOutput& output);

  /**
   * @brief handles the buffering of new data and the broadcast of full buffers
   *
   * @param channel_index the index of the channel being buffered
   * @param new_data the new data to buffer
   * @return int 0 on success, an error code otherwise
   */
  int handle_buffered_data(
    int channel_index, int buffer_index, RawSensorDataOutput& new_data);

  // eliminates warning regarding overload in subclass
  using ASBRTTask<void*, SensorCollectorTask>::init_task;

  /// a convenience typedef for the specialization of BufferPool used
  typedef BufferPool<SensorDataType> DataBuffer;

  // instance variables
  /// the sampling mask of all ADC channels to use
  unsigned long adc_sample_mask;
  /// the maximum buffering allowed to be specified
  size_t max_buffer_count;
  /// the valve to collect data from
  GFCValve* sample_valve;
  /// a Xenomai event that is bound to the ADC interrupts
  ID adc_irq_event;
  /// a BufferPool of SensorDataType buffers for use with buffered output
  DataBuffer buffer_pool;
  /// an array of pointers to pool elements currently being written to
  DataBuffer::WritablePoolElement** active_buffers;
  /// the list of data channel specifications that was provided at initialization
  DataChannel data_channels[MASK_BIT_COUNT];
  /// the number of samples currently buffered for each channel
  int* data_buffering_progress;
  /// the number of samples to buffer on each channel before broadcasting
  int* data_buffering_limit;
};

#endif
