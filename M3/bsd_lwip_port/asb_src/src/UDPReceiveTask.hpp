
/**
 * \ingroup task_instance
 * @brief Definition of the UDPReceiveTask class
 * 
 * @file UDPReceiveTask.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _UDP_RECEIVE_TASK_H
#define _UDP_RECEIVE_TASK_H

#include "ASBRTTask.hpp"
#include "TaskMessages.hpp"
#include "UDPCollector.hpp"

/**
 * \ingroup task_instance
 * @brief The UDPReceiveTask receives data and forwards the control packets
 * 
 * The UDPReceiveTask receives data into \ref PositionControlPacket instances
 * and passes them on to the relevant tasks to be controlled.
 * 
 */
class UDPReceiveTask :
  public ASBRTTask<void*, UDPReceiveTask>,
  public ASBRTProducer<PositionControlPacket>
{
public:
  /**
   * @brief Construct a new UDPReceiveTask object
   * 
   */
  UDPReceiveTask();

  /**
   * @brief initializes this task instance to monitor the given port
   * 
   * @param monitor_port the UDP port to receive on
   * @return int 0 on succes, an error code on failure
   */
  int init_task(int monitor_port);

private:
  /**
   * @brief the primary task function for UDPReceiveTask instances
   * 
   * This function attempts to receive data from the network into a 
   * \ref PositionControlPacket instance, which it then forwards to 
   * connected tasks.
   * 
   * @param instance the task instance this function will work off of
   */
  static void collect_udp_func(UDPReceiveTask* instance);

  /// the UDPCollector instance this task receives from
  UDPCollector<PositionControlPacket, 1> udp_collector;
};

#endif
