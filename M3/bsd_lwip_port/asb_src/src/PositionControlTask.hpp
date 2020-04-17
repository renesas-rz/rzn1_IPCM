
/**
 * \ingroup task_instance
 * @brief Definition of the PositionControlTask class
 * 
 * This task controls the position of the GFC Valve based on the most recent
 * position capacitor data and the network control.
 * 
 * @file PositionControlTask.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _POSITION_CONTROL_TASK_H
#define _POSITION_CONTROL_TASK_H

#include "ASBRTTask.hpp"
#include "TaskMessages.hpp"
#include "GFCValve.hpp"
#include "PIDHandler.hpp"

/// mask for raw data input events
#define NEW_RAW_DATA    0x1
/// mask for network command events
#define NEW_NET_COMMAND 0x2
/// number of samples to average for cap calibration
#define CAP_CALIB_COUNT 10 

/**
 * \ingroup task_instance
 * @brief The PositionControlTask controls the position of the GFC Valve
 * 
 * The PositionControlTask integrates \ref RawSensorDataOutput and 
 * \ref PositionControlPacket data to control a GFCValve to a desired position.
 * This is accomplished through use of the PID algorithm in combination with
 * network based control packets. 
 * 
 */
class PositionControlTask :
  public ASBRTTask<void*, PositionControlTask>,
  public ASBRTEventReceiver<RawSensorDataOutput>,
  public ASBRTEventReceiver<PositionControlPacket>
{
public:
  /**
   * @brief Construct a new Position Control Task object
   * 
   * @param control_valve the GFCValve instance to control
   * @param pid_handler the PIDHandler instance to use
   */
  PositionControlTask(
    GFCValve* control_valve, PIDHandler* pid_handler);

private:
  /// declared private to prevent use
  PositionControlTask();

  /**
   * @brief the primary task function for PositionControlTask instances
   * 
   * This function sets the valve position to zero and then enters its main 
   * loop. This loop consists of
   *  - Wait for new raw data or network command
   *  - If this is the first iteration, use the first few data samples to 
   *    calibrate the capacitance sensor at 0 position
   *  - If calibration is complete, use the new position datapoint to step
   *    the PID control
   *  - if a network command has arrived, carry out the indicated action such
   *    as chaning the PID setpoint
   * 
   * @param instance of the task this function will work off of
   */
  static void position_control_func(PositionControlTask* instance);

  /**
   * @brief Waits for new message to consume and fills appropriate references
   * 
   * This function waits on a new RawSensorDataOutput message, a new 
   * PositionControlPacket message or both and returns a mask indicating which
   * channels were filled.
   * 
   * @param output_mask an OR'd bitmask of datatypes that were retrieved
   * @param new_data a raw data reference to fill
   * @param control a control packet reference to fill
   * @return int 0 on success, an error code otherwise
   */
  int retrieve_new_data(
    unsigned long& output_mask,
    RawSensorDataOutput& new_data, 
    PositionControlPacket& control);

  /**
   * @brief handles a new raw data message by adjusting the position of the 
   * controlled valve as appropriate
   * 
   * This function currently steps the PID on a new capacitor sensor 
   * data point and adjusts the valve position accordingly if not in position
   * override.
   * 
   * @param new_data the new data to consider
   * @return int 0 on success, an error code otherwise
   */
  int handle_raw_data(RawSensorDataOutput& new_data);

  /**
   * @brief handles a new control packet by carrying out its command
   * 
   * @param new_control the new control packet
   * @return int 0 on success, an error code otherwise
   */
  int handle_control_packet(PositionControlPacket& new_control);
  
  /// The valve under control by this task
  GFCValve* control_valve;
  /// the PIDHandler instance to make use of
  PIDHandler* pid_handler;
  /// the calibrated average value of the cap sensor at zero position
  int32_t cap_baseline;
  /// the running total used during calibration
  int64_t calibration_total;
  /// the number of calibration samples collected so far
  int calibration_count;
  /// the previously set GFC Valve Position
  int32_t last_gfcvp;
  /// if true, the position is being overriden due to a network command
  bool in_position_override;
  /// sequencing counter, used to monitor the lost incoming messages
  size_t last_counter;
};

#endif
