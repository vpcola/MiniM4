#include "ioext.h"

LedIO::LedIO(I2C & i2c, uint16_t devaddress, uint32_t clockSpeed)
:   SharedI2C(i2c, clockSpeed),
    _devaddress(devaddress)
{
}

void LedIO::init()
{
    // Initialize the peripheral
    uint8_t buffer[2];

    buffer[0] = 0x00; // Output reg
    buffer[1] = 0x00; // all output

    SharedI2C::write((_devaddress << 1), buffer, 2);
}

void LedIO::write(uint8_t data)
{
    uint8_t buffer[2];

    buffer[0] = 0x14;
    buffer[1] = data;

    SharedI2C::write((_devaddress << 1), buffer, 2);
}



