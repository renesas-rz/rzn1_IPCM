#include "ADS1256.hpp"
#include "SPI.hpp"
#include <stdio.h>


int ADS1256::sendCommand(ADS1256_CMD cmd)
{

  SPI::write(cmd, SlaveSelect);

  return 0;
}


int ADS1256::getRegister(ADS1256_REG reg)
{
  int value;
  SPI::write(0x10 | reg, SlaveSelect);
  SPI::write(0x00, SlaveSelect);

  // according to ADS1256 manual 50 (fifty) clocks delay should be between command and data received back
  // ADS1256 frequency is 8 MHz (1/8000000*50*1000*1000) - time in microseconds - results in 6.25 microsecond.
  busy_delay_7usec();

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  value = SPI::read(SlaveSelect);
  return value;
}


int ADS1256::setRegister(ADS1256_REG reg, int value)
{


  SPI::write(0x50 | reg, SlaveSelect);
  SPI::write(0x00, SlaveSelect);
  SPI::write(value, SlaveSelect);

  return 0;
}





// The ADS1255/6 output 24 bits of data in Binary Two’s Complement format. The LSB has a weight of
// 2V REF /(PGA(2 23 - 1)). A positive full-scale input produces an output code of 7FFFFFh and the negative full-scale
// input produces an output code of 800000h.
int ADS1256::read(Int32 *read_value)
{
  int value = 0;
  unsigned char _highByte, _midByte, _lowByte;

  // An attempt to use FIFO SPI access causes the occasional out of range readings. Slowing SCLK down to 1 Mhz didn't show any improvement.
  // Should be investigated further. Switching back to one-by-one readings.
#if 0
  // to clear SPI FIFO
  clearFIFO();

  FIFOwriteread(&deviceData, SlaveSelect);

  value = ((Int32)deviceData.miso[0] << 16) |((Int32)deviceData.miso[1] << 8) | ((Int32)deviceData.miso[2]);

  if (value & 0x00800000)
  {
    value |= 0xff000000;
  }

  *read_value = value;

  return 0;
#endif

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  _highByte = SPI::read(SlaveSelect);
  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  _midByte = SPI::read(SlaveSelect);
  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  _lowByte = SPI::read(SlaveSelect);
  value = ((Int32)_highByte << 16) |((Int32)_midByte << 8) | ((Int32)_lowByte);

  if (value & 0x00800000)
  {
    value |= 0xff000000;
  }
  *read_value = value;

  return 0;
}

ADS1256::ADS1256(ADS1256_Devices ss, SPI_Channel ch):SPI(ch)
{
  SlaveSelect = ss;  // check range

  deviceData.size = 3;
  deviceData.miso = new UInt8[deviceData.size];
  deviceData.mosi = new UInt8[deviceData.size];

  deviceData.mosi[0] = SPI_DUMMY_BYTE;
  deviceData.mosi[1] = SPI_DUMMY_BYTE;
  deviceData.mosi[2] = SPI_DUMMY_BYTE;

}


int ADS1256::setMUX(Int32 mux_value)
{


  SPI::write(0x51, SlaveSelect);

  SPI::write(0x00, SlaveSelect);

  SPI::write((mux_value & 0xFF), SlaveSelect);

  return 0;
}


int ADS1256::readOneShot(Int32 *value)
{
  sendCommand(RDATA);

  busy_delay_7usec();

  ADS1256::read(value);

  return 0;
}



int ADS1256::getAllRegisters(ADS1256Registers &registers)
{


  SPI::write(0x10, SlaveSelect);
  SPI::write(0x0A, SlaveSelect);

  busy_delay_7usec();

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.status = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.mux = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.adcon = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.drate = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.io = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.ofc0 = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.ofc1 = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.ofc2 = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.fsc0 = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.fsc1 = SPI::read(SlaveSelect);

  SPI::write(SPI_DUMMY_BYTE, SlaveSelect);
  registers.fsc2 = SPI::read(SlaveSelect);

  return 0;
}


int ADS1256::waitUntilDataReady(void)
{
    int bit_n, mask;

    // REDO to look up table
    switch (SlaveSelect)
    {
      case UP_PRESSURE:
        bit_n = 4;
        mask = 1 << bit_n;
        break;
      case DOWN_PRESSURE:
        bit_n = 24;
        mask = 1 << bit_n;
        break;
      case TEMPERATURE:
        bit_n = 23;
        mask = 1 << bit_n;
        break;
      case POSITION:
        bit_n = 29;
        mask = 1 << bit_n;
        break;
      default:
        break;
    }

    while (((BGPIO1->rGPIO_ext_porta.LONG & mask) >> bit_n) != 1)
    {
    ;
    }

  return 0;
}

/* the keyword 'volatile' is used to honor the empty cycles with compiler optimization */
void busy_delay_7usec(void)
{
  for(volatile uint32_t i = 0 ; i < 69u ; i++)
    ;
}

void busy_delay_2usec(void)
{
  for(volatile uint32_t i = 0; i < 20u ; i++)
    ;
}
