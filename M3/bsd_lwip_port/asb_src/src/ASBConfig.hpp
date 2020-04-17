
#ifndef _ASB_CONFIG_H_
#define _ASB_CONFIG_H_

/**
 * \ingroup application 
 * @brief A simple configuration parsing and storage struct.
 * 
 * @file ASBConfig.hpp
 * @author Christopher Sund
 * @date 2018-03-22
 */

#include <string>


// this is an adjustment coefficient of sampling rates of ADS1256. The datasheet values should be adjusted since its oscillator is 8 Mhz instead of 7.68 Mhz
#define ADC1256_RATE_ADJUST (1042/1000)

  /**
   * @brief mapping of a human readable enum to sample rates
   * 
   */
  enum ADCSampleRate
  {
    ADC_SAMPLE_50SPS   = 0x63,
    ADC_SAMPLE_60SPS   = 0x72,
    ADC_SAMPLE_100SPS  = 0x82,
    ADC_SAMPLE_500SPS  = 0x92,
    ADC_SAMPLE_1000SPS = 0xA1,
    ADC_SAMPLE_2000SPS = 0xB0,
    ADC_SAMPLE_3750SPS = 0xC0,
    ADC_SAMPLE_7500SPS = 0xD0
  };


 

/**
 * \ingroup application 
 * @brief the configuration class for the main ASB process
 * 
 */
struct ASBConfig
{
  /**
   * @brief Construct a new ASBConfig object
   * 
   */
  ASBConfig();


  enum ASBConfigError
  {
    ASBConfigError_OK = 0,
    ASBConfigError_NO_POS_ARGS,
    ASBConfigError_CANNOT_CONVERT,
    ASBConfigError_BAD_SAMPLE_RATE,
    ASBConfigError_BAD_FLAG,
    ASBConfigError_BAD_PID_PARAM,
    ASBConfigError_BAD_PORT
  };

  /// the IP address to send collected data to
  std::string receiver_address;
  /// the base port for outputting each data channel
  int base_output_udp_port;
  /**
   * @brief the number of samples to buffer before sending over the network
   * for the capacitor sensor
   */
  int adc_capacitor_buffering;
  /**
   * @brief the number of samples to buffer before sending over the network
   * for the pressure sensor
   */
  int adc_up_pressure_buffering;
  /**
   * @brief the number of samples to buffer before sending over the network
   * for the pressure ONE sensor
   */
  int adc_down_pressure_buffering;
  /**
   * @brief the number of samples to buffer before sending over the network
   * for the temperature sensor
   */
  int adc_temperature_buffering;
  /**
   * @brief the rate at which to sample as a 2 byte short; see ADCSampleRate
   * for mapping to actual sample rate.
   */
  int adc_sample_rate;
  /**
   * @brief the number of output channels this ASB will produce
   * 
   */
  int asb_channel_count;
  /**
   * @brief a temporary config string containing characters that indicate which 
   * channels this ASB should collect
   * 
   */
  std::string channel_config_string;

    /**
   * @brief an array containing the overriden PID parameters; if all zero, the
   * PID option was not specified
   * 
   */
  unsigned long pid_parameters[3];

  /**
   * @brief converts a command line index to a sample rate
   * 
   * @param index an index from 0 to # of elements in ADCSampleRate
   * @return int the sample rate as specified
   */
  static int index_to_sample_rate(int index);

  /**
   * @brief updates the given ASBConfig object to reflect the given command
   * line options.
   * 
   * @param output the instance to be updated
   * @param argc the number of arguments
   * @param argv the arguments as an array of c-strings
   * @return int 0 on success, an error code on failure
   */
  static ASBConfigError from_cli_arguments(
    ASBConfig& output, int argc, char** argv);
  
  static unsigned int sample_rate_to_freq(int sample_rate);

  static const char* asb_config_err_to_message(ASBConfigError);

  /// a usage string to print when malformed arguments are given
  std::string usage_str;
  /// a help string to print (current not implemented)
  std::string help_str;
};

#endif
