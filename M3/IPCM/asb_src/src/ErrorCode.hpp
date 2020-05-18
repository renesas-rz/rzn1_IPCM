// ErrorCode.hpp
//
// (c) 2010-2011 by Pivotal Systems Corp
// All rights reserved.  Company Confidential.
//
// This file contains all GFC error codes.
//
// Created by: Abhijit Majumdar
//
//    $Author: jcheng $
//  $Revision: 1.48 $

#ifndef ERRORCODE_H_
#define ERRORCODE_H_
#include <string>

typedef enum {

  // One's
  ERR_NONE = 0,                  // no error
  ERR_UNDEFINED,                 // undefined error
  ERR_UNSUPPORTED_FUNCTIONALITY, // unsupported functionality
  ERR_INIT_SYNC_OBJ,             // failed to construct synchronized object
  ERR_INIT_QUEUE,                // failed to constructing queue
  ERR_INIT_TASK,                 // failed to create task
  ERR_INIT_MAP,                  // failed to initialize map
  ERR_INIT_SPI_PRESSURE,         // failed to initialize pressure device
  ERR_INIT_SPI_PRESSURE_1,       // failed to initialize pressure 1 device
  ERR_INIT_SPI_TEMPERATURE,      // failed to initialize temperature device
  ERR_INIT_SPI_FEEDBACK,         // failed to initialize feedback device
  ERR_INIT_SPI_PIEZO,            // failed to initialize piezo device

  // Ten's
  ERR_CALIB_SENSOR_ADC,               // 10, failed to calibrate sensor board
                                      // ADC devices
  ERR_VALVE_OVERRIDE_DEV_UNAVAILABLE, // error in opening the device for
                                      // reading valve override and temperature
  ERR_SETPOINT_DEV_UNAVAILABLE,       // error in opening the device
                                      // for reading set point
  ERR_FLOW_FEEDBACK_DEV_UNAVAILABLE,  // error in opening PWM device
                                      // for writting flow feedback
  ERR_CONFIG_FILE_UNAVAILABLE,        // cannot read config file
  ERR_CONFIG_CONTEXT_UNAVAILABLE,     // invalid context
  ERR_SCHEMA_FILE_UNAVAILABLE,        // cannot read schema file
  ERR_SCHEMA_PARSER_UNAVAILABLE,      // no schema parser available
  ERR_PARSE_SCHEMA,                   // failed to parse schema file
  ERR_INVALID_SCHEMA,                 // invalid schema

  // Twenty's
  ERR_PARSE_XML_NODE,             // 20, failed to parse xml node
  ERR_INVALID_CONFIG_INDEX,       // invalid config index for parameter
  ERR_INVALID_CONFIG_NAME,        // invalid config name for parameter
  ERR_INVALID_CONFIG_DATA_TYPE,   // invalid data type for parameter
  ERR_INVALID_CONFIG_VALUE,       // invalid value for parameter
  ERR_GET_CONFIG_VALUE,           // failed to get parameter value
  ERR_SET_CONFIG_VALUE,           // failed to set parameter value
  ERR_INIT_HASHTABLE,             // failed to initialize hashtable
  ERR_INVALID_KEY_IN_HASHTABLE,   // invalid hashtable key
  ERR_DUPLICATE_KEY_IN_HASHTABLE, // duplicate hashtable key

  // Thirty's
  ERR_MISSING_CONF_PARAM,      // 30, missing configuration parameter
  ERR_SET_PRIMARY_TASK_MODE,   // failed to set task to primary mode
  ERR_SET_SECONDARY_TASK_MODE, // failed to set task to secondary mode
  ERR_INVALID_FILE_DESCRIPTOR, // invalid file descriptor which 
                               // points to a file/device/socket/etc.
  ERR_DEV_IO_FAILURE,          // whenever IOCTL fails
  ERR_VALUE_OUT_OF_RANGE,      // value is not in the valid range,
                               // may not be datatype overflow
  ERR_DATATYPE_OVERFLOW,       // invalid value which is out of range
                               // for data type
  ERR_DIVIDED_BY_ZERO,         // error due to divided by zero
  ERR_MEMORY_ALLOC_ISSUE,      // memory allocation error
  ERR_STATE_CONFLICT,          // error due to GFC state conflicts

  // Fourty's
  ERR_INVALID_PARAM,            // 40, invalid task name
  ERR_RPC_SERVER_INIT_FAILURE,  // failed to initialize rpc server
  ERR_OPEN_PERSIST_CONFIG_DIR,  // failed to open persist folder
  ERR_OPEN_PERSIST_CONFIG_FILE, // failed to open persist file
  ERR_READ_PERSIST_CONFIG_FILE, // failed to read persist file
  ERR_OPEN_FILE,                // failed to open file
  ERR_READ_FILE,                // failed to read from file
  ERR_WRITE_FILE,               // failed to write to file
  ERR_ONBOARD_ADC_INIT,         // failed to initialize adc board
  ERR_ONBOARD_LED_INIT,         // failed to initialize led on board

  // Fifty's
  ERR_INVALID_PIEZO,         // 50, invalid piezo position error
  ERR_RESULT_OVERFLOW,       // error due to overflow
  ERR_OPEN_GFM_VALVE,        // failed to open GFM valve
  ERR_INIT_GFM,              // failed to initialize GFM
  ERR_PWM_NOT_READY,         // error due to PWM is not ready to operate
  ERR_NO_GAS_AVAILABLE,      // no GAS is configured for GFC
  ERR_INVALID_GAS,           // invalid GAS specified for GFC
  ERR_TASK_ALREADY_STARTED,  // error due to task is already running
  ERR_TASK_FUNC_UNSPECIFIED, // error due to task is not defined correctly
  ERR_INIT_SPI_PC_PIEZO,     // failed to initialize Pressure Controller

  // Sixty's
  ERR_ANALOG_BOARD_CALIBRATION,   // 60, failed to calibrate analog board
  ERR_PRESSURE_TRANS_READ,        // failed to read pressure or
                                  // position feedback from ADS1256
  ERR_TEMPERATURE_READ,           // failed to read one of the temperatures
  ERR_PREMATURE_STOP,             // Premature procedure abortion
  ERR_STD_EXCEPTION,              // received standard exception
  ERR_INIT_CALIBRATOR,            // failed to initialize Calibrator
  ERR_INVALID_DATA_TYPE,          // invalid data type
  ERR_UNKNOWN_EXCEPTION,          // received unknown (not in std) exception
  ERR_DEVICE_DATA_LINE_NOT_READY,
  ERR_DEVICE_OPEN_FAILURE,

  // Seventy's
  ERR_TEMPERATURE_ERROR_BIT_SET,  // 70
  ERR_TEMPERATURE_PARITY_CHECK_FAILED,
  ERR_TEMPERATURE_NO_DATA_FOR_LONG_TIME,
  ERR_CURR_GAS_ALREADY_SELECTED,
  ERR_NON_CURR_GAS_CREATED,
  ERR_NO_ROR_DATA,
  ERR_DIFF_ROR_TYPE

} ERROR_CODE;

// Structure to encapsulate error code and manages the
// number of occurrences of that error.
struct Error {

private:
  int code; // error code
  int count; // number (0 based) of times the error occurred 
             // before last time it hit the threshold
  int threshold; // when error count is same as this we
                 // say it is enough (and time to log)
  bool countGreaterThanThreshold;                 

public:

  /**
   * Constructor.
   * Param error_threshold
   *       optional number. Default 1.
   *       When error count reaches multiple of this number, 
   *       we will log the error
   */
  Error(int error_threshold = 1) : code (0), count(0), 
    countGreaterThanThreshold(false)  {
    threshold = error_threshold > 0 ? error_threshold : 1;
  }

  /**
   * Sets the error code and changes the counter
   * param  error_code
   *      integer error code, 0 for no error
   */
  void set(const int &error_code){
    // we got the same error code
    if (code == error_code){
      if (code){
        // non-zero error code repeating, so increment the count
        count++;
        if (countGreaterThanThreshold == false)
          countGreaterThanThreshold = (count >= threshold);        
        
        count %= threshold;
      }
      return;
    }

    code = error_code;
    count = 0;
    
  }

  /**
   * returns the error code
   * return current error code
   */
  int get(){
    return code;
  }
  
  /**
   * Indicates if it is too early to log
   * return bool
   *        true if we should log the error, false otherwise
   */
  bool isLoggable(){
    return ((code != 0) && (count == 0));
  }

  /**
   * Did the error take place too many times. This is different
   * from isLoggable because user may want to log regularly, but
   * may perform some operation only when the error count exceeds
   * some threshold.
   *
   * return bool
   *        true if an error take place too many times 
   *        (greater than threshold passed during construction)
   */
  bool tooManyErrors() {
    return countGreaterThanThreshold;
  }
  
  /**
   * Overloaded = operator
   */
  Error& operator=(const Error& err) {
    if (this != &err) {
      this->code = err.code;
      this->threshold = err.threshold;
      this->count = err.count;
    }
    return *this;
  }

  /**
   * Overloaded = operator to set error code
   */
  Error& operator=(const int &error_code) {
    set(error_code);
    return *this;
  }

};// end of structure Error

/**
 * GFC Exception. Sub-modules may throw this exception.
 */
struct GFCException : public std::exception {
   std::string str;
   GFCException(std::string ss) : str(ss) {}
   ~GFCException() throw() {}
   const char* what() const throw() { return str.c_str(); }
};

#endif /*ERRORCODE_H_*/
