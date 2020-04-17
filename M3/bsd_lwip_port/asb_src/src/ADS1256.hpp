#ifndef __ADS1256_HPP__
#define __ADS1256_HPP__

#include "SPI.hpp"

void busy_delay_7usec(void);
void busy_delay_2usec(void);


typedef struct
{
  union
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned long   DRDY:1;
      __IO unsigned long   BUFEN:1;
      __IO unsigned long   ACAL:1;
      __IO unsigned long   ORDER:1;
      __IO unsigned long   ID0:1;
      __IO unsigned long   ID1:1;
      __IO unsigned long   ID2:1;
      __IO unsigned long   ID3:1;
    } BIT;
  } STATUS;
  union
  {
    __IO unsigned long     BYTE;
    struct
    {
      __IO unsigned long   NSEL0:1;
      __IO unsigned long   NSEL1:1;
      __IO unsigned long   NSEL2:1;
      __IO unsigned long   NSEL3:1;
      __IO unsigned long   PSEL0:1;
      __IO unsigned long   PSEL1:1;
      __IO unsigned long   PSEL2:1;
      __IO unsigned long   PSEL3:1;
    } BIT;
  } MUX;
  union
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned long   PG0:1;
      __IO unsigned long   PG1:1;
      __IO unsigned long   PG2:1;
      __IO unsigned long   SDCS0:1;
      __IO unsigned long   SDCS1:1;
      __IO unsigned long   CLK0:1;
      __IO unsigned long   CLK1:1;
      __IO unsigned long   :1;
    } BIT;
  } ADCON;
} ADS1256_Register;

enum ADS1256_Devices { UP_PRESSURE,
                       POSITION,
                       DOWN_PRESSURE,
                       TEMPERATURE};




typedef struct {

  Int32 status;
  Int32 mux;
  Int32 adcon;
  Int32 drate;
  Int32 io;
  Int32 ofc0;
  Int32 ofc1;
  Int32 ofc2;
  Int32 fsc0;
  Int32 fsc1;
  Int32 fsc2;
} ADS1256Registers;




  enum ADS1256_REG { STATUS,
                     MUX,
                     ADCON,
                     DRATE,
                     IO,
                     OFC0,
                     OFC1,
                     OFC2,
                     FSC0,
                     FSC1,
                     FSC2
                     };


  // ADS1256 has more Data Rate Settings. Those are most applicable for our system
  enum ADS1256_RATE {
                      ADC_1256_7500_SPS = 0xD0,
                      ADC_1256_3750_SPS = 0xC0,
                      ADC_1256_2000_SPS = 0xB0,
                      ADC_1256_1000_SPS = 0xA1,
                      ADC_1256_500_SPS = 0x92,
                      ADC_1256_100_SPS = 0x82
                     };


  enum ADS1256_DATA_READY { NOT_READY, READY};

  enum ADS1256_CMD { WAKEUP = 0x00,
                     RDATA  = 0x01,
                     RDATAC = 0x03,
                     SDATAC = 0x0F,
                     RREG,
                     WREG,
                     SELFCAL = 0xF0,
                     SELFOCAL = 0xF1,
                     SELFGCAL = 0xF2,
                     SYSOCAL = 0xF3,
                     SYSGCAL = 0xF4,
                     SYNC = 0xFC,
                     STANDBY =0xFD,
                     RESET = 0xFE,
                     };

class ADS1256 : public SPI
{
  public:

    ADS1256(ADS1256_Devices ss, SPI_Channel ch);

    int read(Int32 *value);
    int readOneShot(Int32 *value);
    int writeRegisters(UInt8 arg_status,
                       UInt8 arg_mux,
                       UInt8 arg_ad_control,
                       UInt8 arg_data_rate_code);

    int waitUntilDataReady();
    int sendCommand(ADS1256_CMD cmd);
    int setMUX(Int32 mux);
    int setRegister(ADS1256_REG reg, int value);
    int getRegister(ADS1256_REG reg);
    int getAllRegisters(ADS1256Registers &registers);


private:
  ADS1256_Devices SlaveSelect;
};
#endif
