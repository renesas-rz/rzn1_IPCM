#include "AD5660.hpp"
#include "SPI.hpp"


AD5660::AD5660(int ss, SPI_Channel ch) : SPI(ch)
{
  deviceData.size = 3;
  deviceData.miso = NULL;
  deviceData.mosi = new UInt8[deviceData.size];
}


int AD5660::write(Int32 dac_cnt)
{

  // AD5660 requires CS edge to start conversion
  SPI::slaveSelect(1); // to change SS mechanism
  SPI::slaveSelect(0);

  // to clear SPI FIFO
  clearFIFO();

  deviceData.mosi[2] = (UInt8)(dac_cnt & 0x000000FF);
  deviceData.mosi[1] = (UInt8)((dac_cnt & 0x0000FF00) >> 8);
  deviceData.mosi[0] = 0x00;

  FIFOwrite(&deviceData, SlaveSelect);

  return 0;
}

