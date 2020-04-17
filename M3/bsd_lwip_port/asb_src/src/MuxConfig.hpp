
#ifndef __MUX_CONFIG_H
#define __MUX_CONFIG_H

#include <cstddef>
#include "TaskMessages.hpp"

struct MuxChannel
{
  size_t positive_channel;
  size_t negative_channel;
  size_t priority;
};

struct MuxConfig
{
  const char* name;
  const MuxChannel* channels;
  const size_t channel_count;
};

#define MUX_VALUE(config) ((config.positive_channel << 4) | config.negative_channel)

#define PRESSURE_MUX_COUNT 1

static const MuxChannel up_pressure_mux[PRESSURE_MUX_COUNT] = {{0x0, 0x1, 1}};

const MuxConfig up_pressure_mux_config =
  {"up_pressure", up_pressure_mux, PRESSURE_MUX_COUNT};

static const MuxChannel down_pressure_mux[PRESSURE_MUX_COUNT] = {{0x0, 0x1, 1}};

const MuxConfig down_pressure_mux_config =
  {"down_pressure", down_pressure_mux, PRESSURE_MUX_COUNT};

#define POSITION_MUX_COUNT 1

static const MuxChannel position_mux[POSITION_MUX_COUNT] = {{0x0, 0x1, 1}};

const MuxConfig position_mux_config =
  {"position", position_mux, POSITION_MUX_COUNT};

#define TEMPERATURE_MUX_COUNT 5

#if(TEMPERATURE_MUX_COUNT == 1)
    #error TEMPERATURE_MUX_COUNT can NOT be 1: no need to multiplex
#endif


/* the followign array represents these temperature signals
  TEMP_PT_UPSTREAM
  TEMP_PT_DOWNSTREAM
  TEMP_BODY_TEMP0
  TEMP_BOARD_TEMP
  TEMP_BODY_TEMP1
*/

const MuxChannel temperature_mux[TEMPERATURE_MUX_COUNT] = {{0x0, 0x8, 1},
                                                           {0x1, 0x8, 1},
                                                           {0x2, 0x8, 1},
                                                           {0x3, 0x8, 1},
                                                           {0x5, 0x8, 1}};

const MuxConfig temperature_mux_config =
  {"temperature", temperature_mux, TEMPERATURE_MUX_COUNT};

inline const MuxConfig* channel_id_to_mux_config(SensorChannelID id)
{
  switch(id)
  {
  case CapSensor:
    return &position_mux_config;
  case DownstreamPressureSensor:
    return &down_pressure_mux_config;
  case UpstreamPressureSensor:
    return &up_pressure_mux_config;
  case TemperatureSensor:
    return &temperature_mux_config;
  default:
    return NULL;
  }
}

#endif
