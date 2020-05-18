
/**
 * \defgroup task_messages Task Message Types
 * \brief Inter-task communication data types
 *
 * These classes specify data structures that are used for inter-task
 * communicaiton.
 */

/**
 * \ingroup task_messages
 * @brief definitions of the inter-task communication types
 *
 * Their collection into a single file is done to make sharing of their
 * definition easier and avoid circular dependencies. This file also collects
 * some shared or otherwise frequently modified configuration constants.
 *
 * @file TaskMessages.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _TASK_MESSAGES_H
#define _TASK_MESSAGES_H

#include "BufferPool.hpp"
#include "kernel_id.h"  // to get the ADC IRQ mask values

/// the maxmimum allowed data buffering in SensorCollectorTask
#define MAX_BUFFER_COUNT       20
/// the number of capacitor sensor samples to buffer
#ifdef HIGH_SPEED
#define ADC_CAP_BUFFERING      10
#else
#define ADC_CAP_BUFFERING      15
#endif
/// the number of pressure sensor samples to buffer
#ifdef HIGH_SPEED
#define ADC_UP_PRESSURE_BUFFERING 1
#else
#define ADC_UP_PRESSURE_BUFFERING 15
#endif
/// the number of pressure ONE sensor samples to buffer
#define ADC_DOWN_PRESSURE_BUFFERING 15
/// the number of temperature sensor samples to buffer
#define ADC_TEMPERATURE_BUFFERING 20
/// the number of ADC channels in use in total
#define ADC_CHANNEL_COUNT      4
/// the default ip address to send buffered data to over UDP
#define UDP_RECEIVER_ADDR     "192.168.7.90"
/// the UDP port to listen for commands on
#define UDP_INPUT_PORT        12345
/// the UDP port to output data on
#define UDP_OUTPUT_PORT       55555
/// the default ADC sample rate to use if not specified
#define DEFAULT_SAMPLE_RATE   0xA1 // 1000 SPS
/// the default buffer pool count used in SensorCollectorTask
#define BUFFER_POOL_CAPACITY  64


// PID Constants
/// the initial proportional constant
#define INITIAL_P     1000000
/// the initial integral constant
#define INITIAL_I     10000
/// the initial derivative constant
#define INITIAL_D     10000
/// the maximum possible DAC output counter
#define DAC_MAX_COUNT ((1 << 18) - 1)
/// the maximum possible ADC input counter
#define ADC_MAX_COUNT ((1 << 24) - 1)


// Xenomai range of tasks priorities:[0..99] (inclusive) where 0 is the lowest effective priority
/// The priority of the \ref SensorCollectorTask instance
#define SENSOR_COLLECTOR_PRIO 5 // originally 40
/// The priority of the \ref PositionControlTask instance
#define POSITION_CONTROL_PRIO 4 // originally 30
/// The priority of the \ref UDPReceiveTask instance
#define UDP_RX_PRIO 3  // originally 20
/// The priority of the \ref UDPTransmitTask instance
#define UDP_TX_PRIO 2 // originally 10

/// A convenience typedef so everyone uses the same type for sensor data
typedef unsigned long SensorDataType;

/* --------------- Sensor Data Definition    ----------*/
/**
 * @brief an enum of the possible sensor channels
 *
 */
typedef enum _SensorChannelID
{
  CapSensor,
  UpstreamPressureSensor,
  DownstreamPressureSensor,
  TemperatureSensor,
  SensorChannelsCount,
  Invalid
} SensorChannelID;

inline SensorChannelID sensor_channel_of_code(char code)
{
  switch(code)
  {
  case 'c':
    return CapSensor;
  case 'd':
    return DownstreamPressureSensor;
  case 'u':
    return UpstreamPressureSensor;
  case 't':
    return TemperatureSensor;
  default:
    return Invalid;
  }
}

/**
 * \ingroup task_messages
 * @brief the data structure for communicating raw data
 *
 */
struct RawSensorDataOutput
{
  /// the channel of this raw data, from among \ref SensorChannelID
  SensorChannelID channel_id;
  ///
  size_t mux_channel_index;
  /// the new data this message contains
  SensorDataType data;
};

/**
 * \ingroup task_messages
 * @brief the data structure for communicating buffered data
 *
 */
struct BufferedSensorDataOutput
{
  /// the channel of this raw data, from among \ref SensorChannelID
  SensorChannelID channel_id;
  /// the multiplex sub-channel of this data
  size_t mux_index;
  /// the number of samples this message contains
  size_t buffer_length;
  /// a pointer to a pool element that contains the new data
  BufferPool<SensorDataType>::PoolElement* data;
};

/* --------------- UDP Input Definition    ----------*/

/**
 * @brief an enumeration of possible network command types
 *
 * Curently unused.
 *
 */
enum UDPInputType
{
  PositionControl,
  LogMessage
};

/**
 * \ingroup task_messages
 * @brief the data structure used for new network control messages
 *
 */

struct PositionControlPacket
{
  /// the enumeration of possible controls
  enum ControlID {
    ASB_VALVE_OVERRIDE = 0,
    ASB_PID_SETPOINT,
    ASB_PID_SET_P,
    ASB_PID_SET_I,
    ASB_PID_SET_D,
    ASB_ABS_PID_SETPOINT
  };
  /// the control this message is seeking to adjust
  ControlID control_id;
  /// a message counter for sequencing, currently unenforced
  size_t counter;
  /// the new value for the given control
  int control_point;
} __attribute__ ((__packed__));

union UDPInputPacket
{
  PositionControlPacket position_control;
};

struct UDPInput
{
  UDPInputType packet_type;
  UDPInputPacket packet;
};

/**
 * @brief The header data structure for use in UDP data messageoutput
 *
 */
struct ASBNetworkHeader
{
  /// the sequence counter
  unsigned long counter;
  /// number of ADC samples in UDP packet
  unsigned long num_of_samples;
  /// the duration of each sample in microseconds
  unsigned long sample_duration;
  /// the channel id this buffered data corresponds to
  unsigned long sample_id;
  /// the multiplex index this data corresponds to
  unsigned long mux_index;
} __attribute__((__packed__));

/**
 * \ingroup task_messages
 * @brief the network output data structure
 *
 */
struct ASBNetworkOutput
{
  /// the header containing metadata
  ASBNetworkHeader header;
  /// the buffered data itself
  SensorDataType data[MAX_BUFFER_COUNT];
} __attribute__((__packed__));
// struct is packed for now, otherwise have to put padding in python monitor

#endif
