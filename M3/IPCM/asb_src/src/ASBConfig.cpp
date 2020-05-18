
#include "ASBConfig.hpp"
#include "TaskMessages.hpp"
#include <sstream>

ASBConfig::ASBConfig() :
  receiver_address(UDP_RECEIVER_ADDR),
  base_output_udp_port(UDP_OUTPUT_PORT),
  adc_capacitor_buffering(ADC_CAP_BUFFERING),
  adc_up_pressure_buffering(ADC_UP_PRESSURE_BUFFERING),
  adc_down_pressure_buffering(ADC_DOWN_PRESSURE_BUFFERING),
  adc_temperature_buffering(ADC_TEMPERATURE_BUFFERING),
  adc_sample_rate(DEFAULT_SAMPLE_RATE),
  asb_channel_count(ADC_CHANNEL_COUNT),
  channel_config_string("cdut")
{
  pid_parameters[0] = 0;
  pid_parameters[1] = 0;
  pid_parameters[2] = 0;
  usage_str = "Usage: asb [options] [-h] [[receiver_addr] [output_port]]";
  help_str = "";
}

int ASBConfig::index_to_sample_rate(int index)
{
  switch(index)
  {
  case 0:
    return ADC_SAMPLE_50SPS;
  case 1:
    return ADC_SAMPLE_60SPS;
  case 2:
    return ADC_SAMPLE_100SPS;
  case 3:
    return ADC_SAMPLE_500SPS;
  case 4:
    return ADC_SAMPLE_1000SPS;
  case 5:
    return ADC_SAMPLE_2000SPS;
  case 6:
    return ADC_SAMPLE_3750SPS;
  case 7:
    return ADC_SAMPLE_7500SPS;
  default:
    return -1;
  }
}

ASBConfig::ASBConfigError ASBConfig::from_cli_arguments(
  ASBConfig& output, int argc, char** argv)
{
  std::stringstream ss;
  int formatted_int, argument_idx = 0;
  for(int idx = 0; idx < argc; idx++)
  {
    std::string arg = argv[idx];
    std::string flag;
    // parse flags
    if(arg[0] == '-' && arg.length() == 2)
    {
      flag = arg.substr(1);
      // if this is the last arg the args are badly formatted
      if(idx >= argc)
      {
        return ASBConfigError_NO_POS_ARGS;
      }
      ss.str(argv[++idx]);
      // available flags are c, p and r
      switch(flag[0])
      {
      case 'c':
        if(!(ss >> formatted_int)) return ASBConfigError_CANNOT_CONVERT;
        output.adc_capacitor_buffering = formatted_int;
        break;
      case 'p':
        if(!(ss >> formatted_int)) return ASBConfigError_CANNOT_CONVERT;
        output.adc_up_pressure_buffering = formatted_int;
        break;
      case 't':
        if(!(ss >> formatted_int)) return ASBConfigError_CANNOT_CONVERT;
        output.adc_temperature_buffering = formatted_int;
        break;
      case 'r':
        if(!(ss >> formatted_int)) return ASBConfigError_CANNOT_CONVERT;
        if((output.adc_sample_rate = index_to_sample_rate(formatted_int)) < 0)
        {
          return ASBConfigError_BAD_SAMPLE_RATE;
        }
        break;
      default:
        return ASBConfigError_BAD_FLAG;
      }
    }
    else if(arg.find("--") == 0)
    {
      if(arg.find("pid") == 2)
      {

        ss.clear();
        ss.str(argv[++idx]);

        std::string param_token;
        std::stringstream pid_ss;
        for(size_t pid_idx = 0; std::getline(ss, param_token, ',') && pid_idx < 3; pid_idx++)
        {
          pid_ss.clear();
          pid_ss.str(param_token);
          if(!(pid_ss >> output.pid_parameters[pid_idx]))
          {
            return ASBConfigError_BAD_PID_PARAM;
          }
        }
      }
    }
    else
    {
      // handle regular arguments
      switch(argument_idx)
      {
      case 0:
        output.receiver_address = arg;
        break;
      case 1:
        //ss.str(arg);
        //if(!(ss >> formatted_int)) return ASBConfigError_BAD_PORT;
        //std::istringstream(argv[idx]) >> formatted_int;
        output.base_output_udp_port = atoi(argv[idx]);
        //output.base_output_udp_port = formatted_int;
        break;
      case 2:
        output.channel_config_string = arg;
        output.asb_channel_count = arg.length();
      default:
        break;
      }
      argument_idx++;
    }
  }
  return ASBConfigError_OK;
}

unsigned int ASBConfig::sample_rate_to_freq(int sample_rate)
{
  switch(sample_rate)
  {
  case ADC_SAMPLE_50SPS:
    return 50 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_60SPS:
    return 60 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_100SPS:
    return 100 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_500SPS:
    return 1000 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_1000SPS:
    return 1000 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_2000SPS:
    return 2000 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_3750SPS:
    return 3750 * ADC1256_RATE_ADJUST;
  case ADC_SAMPLE_7500SPS:
    return 7500 * ADC1256_RATE_ADJUST;
  default:
    return 0;
  }
}

const char* ASBConfig::asb_config_err_to_message(ASBConfig::ASBConfigError e)
{
  switch(e)
  {
  case ASBConfig::ASBConfigError_OK:
    return "No Error";
  case ASBConfig::ASBConfigError_NO_POS_ARGS:
    return "Required positional arguments not given";
  case ASBConfig::ASBConfigError_CANNOT_CONVERT:
    return "Cannot convert a given flag argument to an integer";
  case ASBConfig::ASBConfigError_BAD_SAMPLE_RATE:
    return "Bad sample rate given for -r flag";
  case ASBConfig::ASBConfigError_BAD_FLAG:
    return "Unknown flag given";
  case ASBConfig::ASBConfigError_BAD_PID_PARAM:
    return "Unable to convert a given PID paramater to an integer";
  case ASBConfig::ASBConfigError_BAD_PORT:
    return "Unable to interpret given port as an integer";
  default:
    return "Encountered an unknown ASBConfig error";
  }
}
