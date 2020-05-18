
/**
 * \ingroup utility
 * @brief the class definition for PIDHandler
 * 
 * @file PIDHandler.hpp
 * @author Christopher Sund
 * @date 2018-03-23
 */

#ifndef _PID_HANDLER_H
#define _PID_HANDLER_H

#include <stdint.h>
#include <limits.h>
#include "prim.h"

/**
 * \ingroup utility
 * @brief A utility class that internally performs the PID control algorithm
 * 
 * All calculations are done as integral values after scaling from the 
 * specified ranges to the space of [0, MAX_INT/2]. In this way, calculations 
 * may be performed irrespective to the differences in scale of the Process 
 * Variable (PV) and the Control Variable (CV).
 * 
 * Add some documentation about PID here?
 * 
 */
class PIDHandler
{
public:
  /**
   * @brief Construct a new PIDHandler object
   * 
   * @param p the initial proportional constant
   * @param i the initial integral constant
   * @param d the initial derivative constant 
   * @param max_setpoint the maximum setpoint value possible
   * @param max_pv the maximum process variable value possible
   */
  PIDHandler(int32_t p, 
             int32_t i, 
             int32_t d,
             int32_t max_setpoint,
             int32_t max_pv);

  /**
   * @brief Set the proportional constant
   * 
   * @param p the new proportional constant
   */
  void set_p(int32_t p);

  /**
   * @brief Set the integral constant
   * 
   * @param p the new integral constant
   */
  void set_i(int32_t i);

  /**
   * @brief Set the derivative constant
   * 
   * @param p the new derivative constant
   */
  void set_d(int32_t d);

  /**
   * @brief performs a single step of the PID algorithm and returns the result
   * 
   * @param pv_update the new process variable value
   * @param dt the change in time since the last update (unit-less)
   * @return int32_t the PID update result
   */
  int32_t step(int32_t pv_update, int32_t dt); 

  /**
   * @brief Set the setpoint value
   * 
   * @param new_setpoint the new setpoint to set
   */
  void set_setpoint(int32_t new_setpoint);

  /**
   * @brief resets the PID algorithm to its initial state
   * 
   *  - integral accumulator is set to 0
   *  - derivative calculation is invalidated on next step
   *  - current setpoint is set to 0
   */
  void reset();
private:
  /// declared private to prevent use
  PIDHandler();
  /// the current setpoint in [0, MAX_INT/2] space
  int32_t current_setpoint;
  /// the error computed during the previous step in [0, MAX_INT/2] space
  int32_t last_error_value;
  /// the proportional multiplicative constant in [0, MAX_INT/2] space
  int32_t p_factor;
  /// the integral multiplicative constant in [0, MAX_INT/2] space
  int32_t i_factor;
  /// the derivative multiplicative constant in [0, MAX_INT/2] space
  int32_t d_factor;
  /// the integration accumulator in [0, MAX_INT/2] space
  int32_t integral_accumulator;
  /**
   * @brief the scaling factor for converting from PV space to 
   * [0, MAX_INT/2] space
   * 
   */
  int32_t pv_scale_factor;
  /**
   * @brief the scaling factor for converting from CV space to 
   * [0, MAX_INT/2] space
   * 
   */
  int32_t cv_scale_factor;
  /// true on the first update since object creation or reset
  bool first_update;
  /// the synchronization mutex for this object
  ID pid_mutex;
};

#endif
