
#include "UDPReceiveTask.hpp"

UDPReceiveTask::UDPReceiveTask() :
  ASBRTTask<void*, UDPReceiveTask>(
    ASBRTTaskConfig("UDPReceiveTask"),
    UDPReceiveTask::collect_udp_func)
{
  config.task_priority = UDP_RX_PRIO;
}

int UDPReceiveTask::init_task(int monitor_port)
{
  if(!udp_collector.add_port_to_monitor(monitor_port))
  {
    return 1;
  }
  return ASBRTTask<void*, UDPReceiveTask>::init_task();
}

void UDPReceiveTask::collect_udp_func(UDPReceiveTask* instance)
{
  PositionControlPacket output;
  int rc;
  while(1)
  {
    if((rc = instance->udp_collector.receive_datagram(&output)) <= 0)
    {
      // ignore the case of external socket shutdown (which returns exactly 0)
      if(rc < 0)
      {
        TASK_ERROR("UDPReceiveTask::collect_udp_func() encountered "\
                   "an error while receiving data: %d\r\n", rc);
      }
    }
    if(instance->receiver_count() == 0)
    {
      TASK_OUTPUT("collect_udp_func() got data on port %d:\n"\
                    "\tcontrol_id:    %d\n"\
                    "\tcounter:       %u\n"\
                    "\tcontrol_point: %d\n",
                  rc, output.control_id, output.counter, output.control_point);
      continue;
    }
    if((rc = instance->produce(output)))
    {
      TASK_ERROR("UDPReceiveTask::collect_udp_func() encountered "\
                 "an error while producing: %d\r\n", rc);
    }
  }
}
