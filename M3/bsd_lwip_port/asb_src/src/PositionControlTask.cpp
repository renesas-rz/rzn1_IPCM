
#include "PositionControlTask.hpp"

PositionControlTask::PositionControlTask(
  GFCValve* control_valve, PIDHandler* pid_handler) :
  ASBRTTask<void*, PositionControlTask>(ASBRTTaskConfig("position_control"),
                                        PositionControlTask::position_control_func),
  ASBRTEventReceiver<RawSensorDataOutput>(NEW_RAW_DATA),
  ASBRTEventReceiver<PositionControlPacket>(NEW_NET_COMMAND),
  control_valve(control_valve),
  pid_handler(pid_handler),
  cap_baseline(0),
  calibration_total(0),
  calibration_count(0),
  last_gfcvp(0),
  in_position_override(false),
  last_counter(0)
{
  config.task_priority = POSITION_CONTROL_PRIO;
}

void PositionControlTask::position_control_func(PositionControlTask* instance)
{

  RawSensorDataOutput new_data;
  PositionControlPacket new_control_packet;
  int rc;
  unsigned long message_mask = 0;
  // set to 0 to start so we can collect baseline data
  instance->control_valve->setValvePosition(0);
  while(1)
  {
    if((rc = instance->retrieve_new_data(
      message_mask, new_data, new_control_packet)))
    {
      TASK_ERROR("PositionControlTask::position_control_func() "\
                 "encountered an error retrieving data: %d\r\n", rc);
    }
    if(message_mask & NEW_RAW_DATA &&
       (rc = instance->handle_raw_data(new_data)))
    {
      TASK_ERROR("PositionControlTask::position_control_func() "\
                 "encountered an error handling raw data: %d\r\n", rc);
    }
    if(message_mask & NEW_NET_COMMAND &&
       (rc = instance->handle_control_packet(new_control_packet)))
    {
      TASK_ERROR("PositionControlTask::position_control_func() "\
                 "encountered an error handling control packet: %d\r\n", rc);
    }
  }
}

int PositionControlTask::retrieve_new_data(
  unsigned long& output_mask,
  RawSensorDataOutput& new_data,
  PositionControlPacket& control)
{
  int rc = 0;
  if((rc = wait_for_message(output_mask)))
  {
    TASK_ERROR("PositionControlTask::retrieve_new_data() "\
               "encountered an error waiting for data: %d\r\n", rc);
    return rc;
  }
  // using short circuit here to avoid retrieving data when none available
  if(output_mask & NEW_RAW_DATA &&
     (rc = ASBRTEventReceiver<RawSensorDataOutput>::try_retrieve(new_data)))
  {
    TASK_ERROR("PositionControlTask::retrieve_new_data() "\
               "encountered an error retrieving raw data "\
               "despite IRQ signal: %d\r\n", rc);
    return rc;
  }
  if(output_mask & NEW_NET_COMMAND &&
     (rc = ASBRTEventReceiver<PositionControlPacket>::try_retrieve(control)))
  {
    TASK_ERROR("PositionControlTask::retrieve_new_data() "\
               "encountered an error retrieving control packet "\
               "despite IRQ signal: %d\r\n", rc);
    return rc;
  }
  return rc;
}

int PositionControlTask::handle_raw_data(RawSensorDataOutput& new_data)
{
  /* rt_printf("PositionControlTask::handle_raw_data got new data:\n"\
   *             "\tchannel_id: %d\n"\
   *             "\tdata: %u\n", new_data.channel_id, new_data.data);
   */
  int rc;
  int32_t pid_adjustment, new_pv;
  // if we are currently in position override, ignore new raw data
  if(in_position_override)
  {
    return 0;
  }
  switch(new_data.channel_id)
  {
  case CapSensor:
    if(calibration_count < CAP_CALIB_COUNT)
    {
      calibration_total += new_data.data;
      if(++calibration_count >= CAP_CALIB_COUNT)
      {
        cap_baseline = (int32_t)(calibration_total / CAP_CALIB_COUNT);
        TASK_OUTPUT("PositionControlTask::handle_raw_data() "\
               "got cap_baseline: %d\n", cap_baseline);
      }
      break;
    }
    new_pv = cap_baseline - new_data.data;
    // just using 1 for dt for now
    pid_adjustment = pid_handler->step(new_pv, 1);
    last_gfcvp += pid_adjustment;

    // perform clamping
    if(last_gfcvp < 0)
    {
      last_gfcvp = 0;
    }
    else if(last_gfcvp > DAC_MAX_COUNT)
    {
      last_gfcvp = DAC_MAX_COUNT;
    }
    if((rc = control_valve->setValvePosition(last_gfcvp)))
    {
      TASK_ERROR("PositionControlTask::handle_raw_data() encountered an "\
                 "error while setting valve position: %d\r\n", rc);
      return rc;
    }
    break;
  case DownstreamPressureSensor:
    // do nothing with pressure data for now
    break;
  case UpstreamPressureSensor:
    // do nothing with pressure data for now
    break;
  case TemperatureSensor:
    // do nothing with Temperature
    break;

  default:
    throw std::runtime_error("Encountered an unknown channel_id in raw data stream");
  }

  return 0;
}

int PositionControlTask::handle_control_packet(PositionControlPacket& new_control)
{
//  TASK_OUTPUT("new CTRL packet:\r\n" \
//              "\tCTRL ID: %d\r\n" \
//              "\tcnt: %u\r\n" \
//              "\tcontrol_point: %d\r\n",
//              new_control.control_id, new_control.counter, new_control.control_point);

  if ((new_control.counter - last_counter) != 1)
    TASK_ERROR("RX ERROR");

  last_counter = new_control.counter;

  PositionControlPacket::ControlID ctrl_id = new_control.control_id;
  // if we aren't yet done with calibration, ignore this command
  if(calibration_count < CAP_CALIB_COUNT) {
    TASK_ERROR("Got a command while CapSensor calibration was still underway\r\n");
    return 0;
  }
  int new_ctrl_pt = new_control.control_point;
  switch(ctrl_id)
  {
  case PositionControlPacket::ASB_VALVE_OVERRIDE:
    // negative value indicates turn override off
    if(new_ctrl_pt < 0)
    {
      in_position_override = false;
    }
    else if(new_ctrl_pt >= 0)
    {
      in_position_override = true;
      control_valve->setValvePosition(new_ctrl_pt);
    }
    break;
  case PositionControlPacket::ASB_PID_SETPOINT:
    pid_handler->set_setpoint(new_ctrl_pt);
    break;
  case PositionControlPacket::ASB_PID_SET_P:
    pid_handler->set_p(new_ctrl_pt);
    break;
  case PositionControlPacket::ASB_PID_SET_I:
    pid_handler->set_i(new_ctrl_pt);
    break;
  case PositionControlPacket::ASB_PID_SET_D:
    pid_handler->set_d(new_ctrl_pt);
    break;
  case PositionControlPacket::ASB_ABS_PID_SETPOINT:
    new_ctrl_pt = cap_baseline - new_ctrl_pt;
    if(new_ctrl_pt < 0)
    {
      new_ctrl_pt = 0;
    }
    pid_handler->set_setpoint(new_ctrl_pt);
    break;
  default:
    TASK_ERROR(
      "Encountered an unknown control packet control_id: %d\r\n", (int)ctrl_id);
    return -1;
  }
  return 0;
}
