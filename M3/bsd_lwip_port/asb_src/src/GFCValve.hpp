#ifndef __GFCVALVE_HPP__
#define __GFCVALVE_HPP__

#include "SPI.hpp"
#include "ADS1256.hpp"
#include "AD5660.hpp"
#include "MuxConfig.hpp"





#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  Int32 sample;
  Int32 mux_channel;
} GFCValveDataSample;

typedef struct {
  GFCValveDataSample up_pressure;
  GFCValveDataSample down_pressure;
  GFCValveDataSample capSensorValue;
  GFCValveDataSample temperatureSensorValue;
} GFCValveData;


typedef enum {
  GFC_VALVE_NORMAL,
  GFC_VALVE_CLOSING,
  GFC_VALVE_OPENING

} GFCValveState;



class GFCValve {

  private:
    class MultiplexedADS1256 : public ADS1256
    {
    public:
      MultiplexedADS1256(const MuxConfig* config, ADS1256_Devices ss, SPI_Channel ch):
        ADS1256(ss, ch),
        mux_config(config), prio_index(0)
      {
        config_count = mux_config->channel_count;
        working_prio_counts = new size_t[config_count];
        for(unsigned int idx = 0; idx < config_count; idx++)
        {
          working_prio_counts[idx] = mux_config->channels[idx].priority;
        }
        // set multiplex to settings from first entry
//        setMUX(MUX_VALUE(mux_config->channels[0]));
//        syncADConversion();
      }

      int read_next(Int32 * arg_reading, Int32* arg_mux_chan)
      {
        // for simple case, just do default behavior
        if(config_count == 1)
        {
          *arg_mux_chan = 0;
          return read(arg_reading);
        }
        // write out which mux channel was read from
        *arg_mux_chan = prio_index;
        // increment index for next read
        prio_index = (prio_index + 1) % config_count;
        while(working_prio_counts[prio_index] > 0)
        {
          working_prio_counts[prio_index]--;
          if(working_prio_counts[prio_index] == 0) break;
          prio_index = (prio_index + 1) % config_count;
        }
        // reset to initial priority value
        working_prio_counts[prio_index] = mux_config->channels[prio_index].priority;
        setMUX(MUX_VALUE(mux_config->channels[prio_index]));

        // according to ADS1256 manual 4 (four) clocks cycles delay should be between commands
        // ADS1256 frequency is 8 MHz (1/8000000*4*1000*1000) - time in microseconds - results in 0.5 microsecond.
        // we can't make delay 1 usec, so we will wait for 2 usec

        busy_delay_2usec();
        // perform read
        sendCommand(SYNC);
        busy_delay_2usec();
        sendCommand(WAKEUP);
        busy_delay_2usec();

        return readOneShot(arg_reading);
      }

    private:

      const MuxConfig* mux_config;
      size_t config_count;
      size_t* working_prio_counts;
      size_t prio_index;
    };


  public:
    /**
     * Constructor
     */
    GFCValve();

    int initialize(void);

    int getInitError()
    {
      return error;
    }

    int cleanup()
    {
      return 0;
    }

    int readValveData(unsigned long mask_r, GFCValveData *spi_data);

    int setValvePosition(Int32 position, Int32 *value_written = NULL);

  private:
    MultiplexedADS1256 *up_pressure;
    MultiplexedADS1256 *down_pressure;
    MultiplexedADS1256 *spiPosition;
    MultiplexedADS1256 *spiTemperature;
    AD5660 *dac;
    int error;
};


#ifdef __cplusplus
}
#endif


#endif
