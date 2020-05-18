#include "SPI.hpp"
#include "rzn1-memory-map.h"


SPI::SPI(SPI_Channel ch)
{
  spi_channel = ch;
  interface = getInterface(spi_channel);

  deviceData.miso = NULL;
  deviceData.mosi = NULL;
  deviceData.size = 0;
}


bool SPI::isTransmitFIFOEmpty(void)
{
  return interface->rSpi_SR.BIT.bSpi_TFE;
}

bool SPI::isSPIBUSY(void)
{
  return interface->rSpi_SR.BIT.bSpi_BUSY;
}


bool SPI::isRxFIFONotEmpty(void)
{
  return interface->rSpi_SR.BIT.bSpi_RFNE;
}


void SPI::FIFOwrite(spi_transfer_t *data, int ss)
{
  slaveSelect(ss);

  for(int i = 0; i < data->size; i++)
  {
    interface->rSpi_DR.BIT.bSpi_DR = *(data->mosi + i);
  }
  while (interface->rSpi_SR.BIT.bSpi_TFE== 0)
    ;

  while(isSPIBUSY())
    ;
}

void SPI::FIFOwriteread(spi_transfer_t *data, int ss)
{
  slaveSelect(ss);

  for(int i = 0; i < data->size; i++)
  {
    interface->rSpi_DR.BIT.bSpi_DR = *(data->mosi + i);
  }
  while (interface->rSpi_SR.BIT.bSpi_TFE== 0)
    ;

  while(isSPIBUSY())
    ;

  while (interface->rSpi_SR.BIT.bSpi_RFNE == 0)
    ;

  while(isSPIBUSY())
    ;


  for(int i = 0; i < data->size; i++)
  {
    data->miso[i] = interface->rSpi_DR.BIT.bSpi_DR;
  }
}

void SPI::write(UInt32 value, int ss)
{

  slaveSelect(ss);

  interface->rSpi_DR.BIT.bSpi_DR = value;

  while (interface->rSpi_SR.BIT.bSpi_TFE== 0)
    ;

  while(isSPIBUSY())
    ;
}


UInt32 SPI::read(int ss)
{

  slaveSelect(ss);

  while (interface->rSpi_SR.BIT.bSpi_RFNE == 0)
    ;

  while(isSPIBUSY())
    ;

  return interface->rSpi_DR.LONG;
}


UInt32 SPI::getSPISelectSlave(void)
{

  return (interface->rSpi_SER.LONG);
}

void SPI::slaveSelect(unsigned int ss)
{

  switch (ss)
  {
  case 0:
    interface->rSpi_SER.BIT.bSpi_SoftwareSS = 1;
    break;
  case 1:
    interface->rSpi_SER.BIT.bSpi_SoftwareSS = 2;
    break;
  case 2:
    interface->rSpi_SER.BIT.bSpi_SoftwareSS = 4;
    break;
  case 3:
    interface->rSpi_SER.BIT.bSpi_SoftwareSS = 8;

    break;

  }

}

void SPI::clearFIFO(void)
{
  disable();
  enable();
}


void SPI::disable(void)
{

  interface->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;
}


void SPI::enable(void)
{

  interface->rSpi_SSIENR.BIT.bSpi_SSIENR = 1;
}

inline unsigned int SPI::getStatus(void)
{

  return interface->rSpi_SR.LONG;
}


int SPI::init(int SPIClockDivider, SPI_Channel ch)
{
  volatile SPI_M_Type *spi_address;

  switch (ch)
  {
    case SPI_CH_1:
      spi_address = SPI1;
      break;

    case SPI_CH_2:
      spi_address = SPI2;
      break;
  }

  // disable the SPI channel
  spi_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;


  spi_address->rSpi_CTRLR0.BIT.bSpi_DFS = 0;
  spi_address->rSpi_CTRLR0.BIT.bSpi_FRF = 0;
  spi_address->rSpi_CTRLR0.BIT.bSpi_SCPH = 1;
  spi_address->rSpi_CTRLR0.BIT.bSpi_SCPOL = 0;
  spi_address->rSpi_CTRLR0.BIT.bSpi_TMOD = 0;
  spi_address->rSpi_CTRLR0.BIT.bSpi_SLV_OE = 0; // Slave Output Enable (SPI slave only)
  spi_address->rSpi_CTRLR0.BIT.bSpi_SRL = 0; // Shift Register Loop Used for testing purposes only
  spi_address->rSpi_CTRLR0.BIT.bSpi_CFS = 7;

  spi_address->rSpi_CTRLR1.LONG = 0; // Nr dataframes + 1 minimum. Should not have effect as TMOD=tx+rx.

  spi_address->rSpi_MWCR.LONG = 0; // Microwire Control - N/A
  spi_address->rSpi_TXFLR.LONG = 0; // Interrupt when 0 data available in Tx FIFO.
  spi_address->rSpi_RXFLR.LONG  = 0; // interrupt when 1 or more data available in Rx FIFO.

  spi_address->rSpi_BAUDR.BIT.bSpi_SCKDV = SPIClockDivider;
  spi_address->rSpi_IMR.LONG = 0x0; //Interrupt Mask Register

  spi_address->rSpi_SER.BIT.bSpi_HardwareSS = 0xf;
  spi_address->rSpi_SER.BIT.bSpi_CtrlSS = 0xf;

  // enable the SPI channel
  spi_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 1;

  return 0;
}


// there are only two Master SPIs in the system
SPI_M_Type volatile *SPI::getInterface(SPI_Channel ch)
{
  switch (ch)
  {
    case SPI_CH_1:
      return SPI1;
      break;

    case SPI_CH_2:
      return SPI2;
      break;

    default:
      return NULL;
      break;
  }
}
