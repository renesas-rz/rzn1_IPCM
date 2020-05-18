#include "GFCValve.hpp"
#include "SPI.hpp"



#include "ADS1256.hpp"
#include "rzn1-memory-map.h"

#include "kernel.h"
#include "kernel_id.h"
#include "asb_low_level_init.h"

/**
 * Constructor
 */
GFCValve::GFCValve()
{
  SPI::init(64, SPI_CH_2);

  SPI::init(64, SPI_CH_1);

  up_pressure = new MultiplexedADS1256(&up_pressure_mux_config, UP_PRESSURE, SPI_CH_2);
  spiPosition = new MultiplexedADS1256(&position_mux_config, POSITION, SPI_CH_2);
  down_pressure = new MultiplexedADS1256(&down_pressure_mux_config, DOWN_PRESSURE, SPI_CH_2);
  spiTemperature = new MultiplexedADS1256(&temperature_mux_config,TEMPERATURE, SPI_CH_2);

  dac = new AD5660(0, SPI_CH_1);
}


int GFCValve::initialize(void)
{

  tslp_tsk(100);
  up_pressure->sendCommand(RESET);
  tslp_tsk(10);
  spiPosition->sendCommand(RESET);
  tslp_tsk(10);
  down_pressure->sendCommand(RESET);
  tslp_tsk(10);
  spiTemperature->sendCommand(RESET);
  tslp_tsk(10);


  up_pressure->setRegister(DRATE, ADC_1256_1000_SPS);

  tslp_tsk(10);

#ifdef HIGH_SPEED
  spiPosition->setRegister(DRATE, ADC_1256_7500_SPS);
#else
  spiPosition->setRegister(DRATE, ADC_1256_1000_SPS);
#endif

  tslp_tsk(10);

  down_pressure->setRegister(DRATE, ADC_1256_1000_SPS);

  tslp_tsk(10);

  spiTemperature->setRegister(DRATE, ADC_1256_100_SPS);

  tslp_tsk(10);



  up_pressure->waitUntilDataReady();

  up_pressure->setRegister(STATUS, 0x02);

  tslp_tsk(10);

  spiPosition->waitUntilDataReady();

  spiPosition->setRegister(STATUS, 0x02);

  tslp_tsk(10);


  down_pressure->waitUntilDataReady();

  down_pressure->setRegister(STATUS, 0x02);

  tslp_tsk(10);



  spiTemperature->waitUntilDataReady();

  spiTemperature->setRegister(STATUS, 0x02);

  tslp_tsk(10);


  up_pressure->waitUntilDataReady();

  up_pressure->setRegister(MUX, 0x01);

  tslp_tsk(10);



  spiPosition->waitUntilDataReady();

  spiPosition->setRegister(MUX, 0x01);

  tslp_tsk(10);


  down_pressure->waitUntilDataReady();

  down_pressure->setRegister(MUX, 0x01);

  tslp_tsk(10);



  spiTemperature->waitUntilDataReady();

  spiTemperature->setRegister(MUX, 0x01);

  tslp_tsk(10);



  up_pressure->waitUntilDataReady();

  up_pressure->setRegister(ADCON, 0x22);

  tslp_tsk(10);



  spiPosition->waitUntilDataReady();

  spiPosition->setRegister(ADCON, 0x20);

  tslp_tsk(10);



  down_pressure->waitUntilDataReady();

  down_pressure->setRegister(ADCON, 0x22);

  tslp_tsk(10);



  spiTemperature->waitUntilDataReady();

  spiTemperature->setRegister(ADCON, 0x21);

  tslp_tsk(10);

  up_pressure->waitUntilDataReady();
  up_pressure->sendCommand(SELFCAL);
  tslp_tsk(10);

  spiPosition->waitUntilDataReady();
  spiPosition->sendCommand(SELFCAL);
  tslp_tsk(10);

  down_pressure->waitUntilDataReady();
  down_pressure->sendCommand(SELFCAL);
  tslp_tsk(10);

  spiTemperature->waitUntilDataReady();
  spiTemperature->sendCommand(SELFCAL);
  tslp_tsk(10);



  up_pressure->waitUntilDataReady();
  up_pressure->sendCommand(RDATAC);
  tslp_tsk(10);

  spiPosition->waitUntilDataReady();
  spiPosition->sendCommand(RDATAC);
  tslp_tsk(10);

  down_pressure->waitUntilDataReady();
  down_pressure->sendCommand(RDATAC);
  tslp_tsk(10);

  tslp_tsk(10);

  // to intitialise the interrupts after the ADC are set to the operational rates
  // otherwise the high interrupts load my break the process
  ASB_SB_IRQs_init();

  return 0;
}


int GFCValve::readValveData(unsigned long mask_r, GFCValveData *spi_data)
{
  int err = 0;

  if(mask_r & ADC_UP_PRESSURE_MASK)
  {
    err |= up_pressure->read_next(&spi_data->up_pressure.sample, &spi_data->up_pressure.mux_channel);
  }

  if(mask_r & ADC_DOWN_PRESSURE_MASK)
  {
    err |= down_pressure->read_next(&spi_data->down_pressure.sample, &spi_data->down_pressure.mux_channel);
  }

  if(mask_r & ADC_CAP_MASK)
  {
    err |= spiPosition->read_next(&spi_data->capSensorValue.sample, &spi_data->capSensorValue.mux_channel);
  }

  if(mask_r & ADC_TEMPERATURE_MASK)
  {
    err |= spiTemperature->read_next(&spi_data->temperatureSensorValue.sample, &spi_data->temperatureSensorValue.mux_channel);
  }

  return 0;
}


int GFCValve::setValvePosition(Int32 position, Int32 *value_written)
{
  // Historically the valve code is pretending that it uses 18 bit control of valve. DAC itself is using only 16 bit. That's why we are dividing by 4.
  dac->write(position/4);

  return 0;
}
