#ifndef __SPI_HPP__
#define __SPI_HPP__
#include "atomic"

#include "RZN1D_SFR.h"
#include "Constants.hpp"




#ifdef __cplusplus
extern "C" {
#endif

// this dummy byte is used whenever MOSI write is initiated in order to read MISO line
#define SPI_DUMMY_BYTE 0x02

// structure to pass to SPI driver
typedef struct {
    UInt8 *mosi;   // output buffer
    UInt8 *miso;   // input buffer
    int size;      // size of the buffer
} spi_transfer_t;

enum SPI_Channel {SPI_CH_1, SPI_CH_2, SPI_CH_3, SPI_CH_4};

class SPI
{

  public:


    SPI(SPI_Channel ch);

    static int init(int SPIClockDivider, SPI_Channel ch);

    bool isTransmitFIFOEmpty(void);

    void FIFOwriteread(spi_transfer_t *data, int ss);

    void FIFOwrite(spi_transfer_t *data, int ss);

    bool isSPIBUSY(void);

    bool isRxFIFONotEmpty(void);

    void write(UInt32 value, int ss);

    UInt32 read(int ss);

    void clearFIFO(void);

    UInt32 getSPISelectSlave(void);

    void slaveSelect(unsigned int ss);

    void disable(void);

    void enable(void);

    unsigned int getStatus(void);

protected:
    spi_transfer_t deviceData;
    volatile SPI_M_Type *interface;

private:
    SPI_Channel spi_channel;
    SPI_M_Type volatile *getInterface(SPI_Channel ch);
};


#ifdef __cplusplus
}
#endif

#endif
