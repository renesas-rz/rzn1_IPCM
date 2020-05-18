#ifndef AD5660_H
#define AD5660_H

#include "SPI.hpp"

class AD5660 : public SPI
{
  public:

    AD5660(int ss, SPI_Channel ch);
    int write(Int32 arg_value);
  private:
    int SlaveSelect;

};

#endif
