
#include "PIDHandler.hpp"
#include <cstdio>
#include "ASBRTTask.hpp"

#define PRECISION_SCALE_FACTOR (INT_MAX >> 1)

PIDHandler::PIDHandler(int32_t p, 
                       int32_t i, 
                       int32_t d,
                       int32_t max_cv,
                       int32_t max_pv) : 
  current_setpoint(0), 
  last_error_value(0), 
  integral_accumulator(0),
  first_update(true)
{
  cv_scale_factor = PRECISION_SCALE_FACTOR / max_cv;
  pv_scale_factor = PRECISION_SCALE_FACTOR / max_pv;
  p_factor = p * pv_scale_factor;
  i_factor = i * pv_scale_factor;
  d_factor = d * pv_scale_factor;
  if(hwrtos_prim_get_mtx(&pid_mutex))
  {
    TASK_ERROR("Failed to create pid_mutex\n");
  }
}

void PIDHandler::set_p(int32_t new_p)
{
  if(loc_mtx(pid_mutex))
  {
    TASK_ERROR("Failed to acquire mutex in set_p()\n");
    return;
  }
  p_factor = new_p * pv_scale_factor;
  unl_mtx(pid_mutex);
}

void PIDHandler::set_i(int32_t new_i)
{
  if(loc_mtx(pid_mutex))
  {
    TASK_ERROR("Failed to acquire mutex in set_i()\n");
    return;
  }
  i_factor = new_i * pv_scale_factor;
  unl_mtx(pid_mutex);
}

void PIDHandler::set_d(int32_t new_d)
{
  if(loc_mtx(pid_mutex))
  {
    TASK_ERROR("Failed to acquire mutex in new_d()\n");
    return;
  }
  d_factor = new_d * pv_scale_factor;
  unl_mtx(pid_mutex);
}

int32_t PIDHandler::step(int32_t pv_update, int32_t dt)
{
  if(loc_mtx(pid_mutex))
  {
    TASK_ERROR("Failed to acquire mutex in step()\n");
    return 0;
  }
  // might be faster to store some variables as 64_t to avoid casting?
  pv_update *= pv_scale_factor;
  int32_t error = current_setpoint - pv_update;
  int64_t output = ((int64_t)p_factor) * error;
  integral_accumulator += error;
  // prevent integrator buildup?
  integral_accumulator >>= 1;
  output += ((int64_t)i_factor) * integral_accumulator;
  if(first_update)
  {
    first_update = false;
  }
  else
  {
    output += ((int64_t)d_factor) * ((error - last_error_value) / dt);
  }
  last_error_value = error;
  output /= ((int64_t)pv_scale_factor * PRECISION_SCALE_FACTOR);
  unl_mtx(pid_mutex);
  return (int32_t)output;
}

void PIDHandler::set_setpoint(int32_t new_setpoint)
{
  if(loc_mtx(pid_mutex))
  {
    TASK_ERROR("Failed to acquire mutex in set_setpoint()\n");
    return;
  }
  new_setpoint *= pv_scale_factor;
  integral_accumulator = 0;
  current_setpoint = new_setpoint;
  unl_mtx(pid_mutex);
}
