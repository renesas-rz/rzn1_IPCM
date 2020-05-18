
/**
 * \mainpage Autonomous Sensor Board
 * 
 * \section Introduction
 * 
 * The Autonomous Sensor Board (ASB) is intended to provide a modular software
 * and hardware platform for control of hardware devices on a physical sensor 
 * board. This application is intended to be run as firmware on the sensor 
 * board under a linux environment. It collects sensor data from ADCs and 
 * controls output devices via DACs. 
 * 
 * Currently the ASB provides the following high level features:
 *  (1) Hardware device interfacing:
 *    - collects data from connected ADCs and writes output to connected
 *      DACs
 *  (2) Network interface over UDP
 *    - Receives control packets from a master/masters over a TCP/IP network
 *    - outputs collected raw data over the network
 *  (3) PID control of coupled signals
 *    - currently this is implemented to provide PID control of a GFC valve
 *      with the Capacitance Sensor counter as the PV and the DAC counter
 *      as the CV.
 * 
 * This functionality is divided across 4 real time tasks:
 *  - SensorCollectorTask: collects data from on board physical sensors
 *  - UDPReceiveTask: collects commands from a master/masters over network
 *  - PositionControlTask: uses collected raw data to control a DAC via PID
 *  - UDPTransmitTask: broadcasts buffered data
 */

/**
 * \defgroup application ASB Application
 * \brief Application entrypoint and low level configuration
 * 
 */

/**
 * \ingroup application 
 * @brief  Main Application Entrypoint and Xenomai Initialization
 *  Source file for the primary entry point to the ASB application.
 *  This file contains the application main and a simple signal 
 *  handler for ctrl-C's.
 * 
 * @file main.cpp
 * @author Christopher Sund
 * @date 2018-03-22
 */

#include "SensorCollectorTask.hpp"
#include "PositionControlTask.hpp"
#include "UDPTransmitTask.hpp"
#include "UDPReceiveTask.hpp"
#include "ASBConfig.hpp"
#include "GFCValve.hpp"
#include "PIDHandler.hpp"
#include "TaskMessages.hpp"
#include "prim.h"
#include "kernel.h"
#include "asb_low_level_init.h"





/// clock rate of SPI in Hz; just using 1MHz for now since it seems stable
#define SPI_CLOCKRATE 1000000
/// maximum buffering for each channel in the sensor collector task
#define BUFFER_COUNT 20
/// number of microseconds in a second
#define MICRO_PER_SECOND 1000000


/// the running state of the overall application
static bool program_running = true;

/**
 * @brief main program entry point; arguments are parsed into an ASBConfig 
 * instance.
 * 
 * @param argc number of arguments
 * @param argv arguments as an array of c-strings
 * @return int 0 on clean exit; non-zero exit code on encountering an error
 */
int asb_main(int argc, char** argv)
{
  tslp_tsk(5000);

  // ---------- parse command line args ----------
  ASBConfig asb_config;
  ASBConfig::ASBConfigError config_err;
  if((config_err = ASBConfig::from_cli_arguments(asb_config, argc - 1, &argv[1])))
  {
    const char* err_message = ASBConfig::asb_config_err_to_message(config_err);
    TASK_ERROR("Unable to parse command line arguments: %s;\r\n", err_message);
    TASK_ERROR("%s\r\n", asb_config.usage_str.c_str());
    return 1;
  }
  // restore defaults as necesssary
  for(size_t idx = 0; idx < 3; idx++)
  {
    if(asb_config.pid_parameters[idx] == 0)
    {
      switch(idx)
      {
      case 0:
        asb_config.pid_parameters[idx] = INITIAL_P;
        break;
      case 1:
        asb_config.pid_parameters[idx] = INITIAL_I;
        break;
      case 2:
        asb_config.pid_parameters[idx] = INITIAL_D;
        break;
      }
    }
  }
  TASK_OUTPUT("Got configuration:\r\n"
              "\tASB ID: %d\r\n"
              "\treceiver_addr: %s\r\n",
              ASB_ID,
              asb_config.receiver_address.c_str());


  TASK_OUTPUT("\toutput_udp_port: %d\r\n"
                "\tadc_capacitor_buffering: %d\r\n",
              asb_config.base_output_udp_port,
              asb_config.adc_capacitor_buffering);

  TASK_OUTPUT("\tadc_pressure_buffering: %d\r\n"
              "\tadc_sample_rate: %d\r\n",
              asb_config.adc_up_pressure_buffering,
              asb_config.adc_sample_rate);

  TASK_OUTPUT("\tchannel_config_string: %s\r\n"
              "\tasb_channel_count: %d\r\n",
              asb_config.channel_config_string.c_str(),
              asb_config.asb_channel_count);

  TASK_OUTPUT("\tpid_values: [%d, %d, %d]\r\n",
              asb_config.pid_parameters[0],
              asb_config.pid_parameters[1],
              asb_config.pid_parameters[2]);

  // ---------- set up physical devices ----------
  //TASK_OUTPUT("Setting up physical devices...\r\n");
  int rc;
  GFCValve gfc_valve;
  if(rc = gfc_valve.initialize())
  {
    TASK_ERROR("Encountered error while initializing GFC Valve: %d\r\n", rc);
    return rc;
  }

  // ---------- set up PID Loop ----------
  PIDHandler pid_handler(
    asb_config.pid_parameters[0], asb_config.pid_parameters[1], asb_config.pid_parameters[2],
    DAC_MAX_COUNT, ADC_MAX_COUNT);

  // ---------- create tasks ----------
  //TASK_OUTPUT("Instantiating tasks...\r\n");
  SensorCollectorTask sensor_task(BUFFER_COUNT, &gfc_valve);
  PositionControlTask position_task(&gfc_valve, &pid_handler);
  UDPTransmitTask udp_tx_task;
  UDPReceiveTask udp_rx_task;

  // ---------- connect messages ----------
  //TASK_OUTPUT("Connecting task messages...\r\n");
  TASK_CONNECT(&sensor_task, &position_task, RawSensorDataOutput);
  TASK_CONNECT(&sensor_task, &udp_tx_task, BufferedSensorDataOutput);
  TASK_CONNECT(&udp_rx_task, &position_task, PositionControlPacket);

  // ---------- initialize tasks ----------
  //TASK_OUTPUT("Initializing tasks...\r\n");
  int adc_channel_count = asb_config.channel_config_string.length();
  //TASK_OUTPUT("Allocating channel_array\r\n");
  SensorCollectorTask::DataChannel* channel_array = 
    new SensorCollectorTask::DataChannel[adc_channel_count];
  //TASK_OUTPUT("Filling channel_array %p\r\n", (void*)channel_array);
  for(int channel = 0; channel < adc_channel_count; channel++)
  {
    if(SensorCollectorTask::DataChannel::data_channel_of_code(
      channel_array[channel], asb_config.channel_config_string[channel], asb_config))
    {
      TASK_ERROR("main() was unable to fill the sensor collector task channel_array\r\n");
      delete[] channel_array;
      return 1;
    }
  }
  //TASK_OUTPUT("SensorCollectorTask running init_task()\r\n");
  if((rc = sensor_task.init_task(&channel_array[0], adc_channel_count)))
  {
    TASK_ERROR("main() encountered an error while initializing "\
               "sensor_task: %d\r\n", rc);
    delete[] channel_array;
    return rc;
  }
  //TASK_OUTPUT("SensorCollectorTask done\r\n");
  if((rc = position_task.init_task()))
  {
    TASK_ERROR("main() encountered an error while initializing "\
               "position_task: %d\r\n", rc);
    delete[] channel_array;
    return rc;
  }
  //TASK_OUTPUT("PositionControlTask done\r\n");
  unsigned int sample_rate = 
    ASBConfig::sample_rate_to_freq(asb_config.adc_sample_rate);
  if(sample_rate == 0)
  {
    TASK_ERROR(
      "Encountered an illegal sample rate %d\r\n", asb_config.adc_sample_rate);
    delete channel_array;
    return 1;
  }
  unsigned int sample_period = 
    MICRO_PER_SECOND / sample_rate;

   UDPTransmitTask::OutputChannelSpec* output_specs = NULL;
  unsigned int total_specs = 0;
  const MuxConfig* mux_config;
  SensorChannelID sensor_id;
  unsigned int spec_index = 0;

  //TASK_OUTPUT("filling transmit specs\r\n");
  for(int channel = 0; channel < adc_channel_count; channel++)
  {
    char channel_code = asb_config.channel_config_string[channel];
    if((sensor_id = sensor_channel_of_code(channel_code)) == Invalid)
    {
      TASK_ERROR("main() encountered an unknown channel code while initializing: "\
                 "%c\r\n", channel_code);
    }
    if((mux_config = channel_id_to_mux_config(sensor_id)) == NULL)
    {
      TASK_ERROR("main() encountered an unknown sensor_id while initializing: "\
                 "%d\r\n", sensor_id);
    }
    for(unsigned int mux_idx = 0; mux_idx < mux_config->channel_count; mux_idx++)
    {
      total_specs++;
    }
  }

  //TASK_OUTPUT("Computed %d total specs\r\n", total_specs);

  output_specs = new UDPTransmitTask::OutputChannelSpec[total_specs];
  
  for(int channel = 0; channel < adc_channel_count; channel++)
  {
    char channel_code = asb_config.channel_config_string[channel];
    sensor_id = sensor_channel_of_code(channel_code);
    mux_config = channel_id_to_mux_config(sensor_id);

    for(size_t mux_index = 0; mux_index < mux_config->channel_count; mux_index++)
    {
      //TASK_OUTPUT("Filling info for spec %d\r\n", spec_index);
      output_specs[spec_index].channel_id = sensor_id;
      output_specs[spec_index].mux_index = mux_index;
      //output_specs[spec_index].netif_name = asb_config.netif_name.c_str();
      output_specs[spec_index].receiver_address = asb_config.receiver_address.c_str();
      output_specs[spec_index].udp_port = asb_config.base_output_udp_port + spec_index;
      output_specs[spec_index].sample_period = sample_period;
      spec_index++;
    }
  }
  if((rc = udp_tx_task.init_task(output_specs, total_specs)))
  {
    TASK_ERROR("main() encountered an error while initializing "\
               "udp_tx_task: %d\r\n", rc);
  }
  //TASK_OUTPUT("UDPTransmitTask done\r\n");

//  for(spec_index = 0; spec_index < total_specs; spec_index++)
//  {
//   TASK_OUTPUT("Will broadcast channel %d, mux %d on address %s\r\n",
//                output_specs[spec_index].channel_id, output_specs[spec_index].mux_index,
//                udp_tx_task.get_transmission_address(spec_index).c_str());
//  }

  if((rc = udp_rx_task.init_task(UDP_INPUT_PORT)))
  {
    TASK_ERROR("main() encountered an error while initializing "\
               "udp_rx_task: %d\r\n", rc);
  }

  //TASK_OUTPUT("UDPReceiveTask done\r\n");
  // ---------- start tasks ----------
  TASK_OUTPUT("Starting tasks...\r\n");
  // start UDP transmit task first
  if((rc = udp_tx_task.start_task(udp_tx_task.config.task_name)))
  {
    TASK_ERROR("main() encountered an error while starting "\
               "udp_tx_task: %d\r\n", rc);
  }
  // next start data collection
  if((rc = sensor_task.start_task(sensor_task.config.task_name)))
  {
    TASK_ERROR("main() encountered an error while starting "\
               "sensor_task: %d\r\n", rc);
  }
  // now start position control
  if((rc = position_task.start_task(position_task.config.task_name)))
  {
    TASK_ERROR("main() encountered an error while starting "\
               "sensor_task: %d\r\n", rc);
  }
  // now start UDP receive for commands
  if((rc = udp_rx_task.start_task(udp_rx_task.config.task_name)))
  {
    TASK_ERROR("main() encountered an error while starting "\
               "udp_rx_task: %d\r\n", rc);
  }
  // ---------- main thread loop ----------
  TASK_OUTPUT("Main thread entering infinite loop...\r\n");
  while(program_running)
  {
    tslp_tsk(100000000LL);
  }
  return 0;
}

extern "C" {
  int asb_main_wrapper(int argc, char** argv) 
  {
    return asb_main(argc, argv);
  }
}

