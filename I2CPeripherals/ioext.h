#ifndef __IO_EXT_H__
#define __IO_EXT_H__

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "sharedi2c.hpp"



#define I2C_EXTIO_PORT 0x21
#define I2C_EXTIO_SPEED 100000

class LedIO : public SharedI2C
{
    public:

    LedIO(I2C & i2c, uint16_t devaddress = I2C_EXTIO_PORT, uint32_t clockSpeed = I2C_EXTIO_SPEED);

    void init();
    
    void write(uint8_t data);

    private:

    uint16_t  _devaddress;
};


#endif
