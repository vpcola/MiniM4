#ifndef __SHARED_I2C_H__
#define __SHARED_I2C_H__

/**
 * Author : Cola Vergil
 * Email  : vpcola@gmail.com
 * Date : Thu Jan 08 2015
 **/

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "i2c.hpp"

#include "platform.h"


class SharedI2C 
{
    public:
        SharedI2C(I2C & i2c, 
            uint32_t clkSpeed,
            uint32_t addressMode = I2C_ADDRESSINGMODE_7BIT,
            uint32_t timeout = I2C_DEFAULT_TIMEOUT);


        void setClkSpeed(uint32_t clkSpeed) { _clkSpeed = clkSpeed; }
        void setAddressMode(uint32_t addressMode) { _addressMode = addressMode; }


        bool read(uint16_t address, uint8_t * data, uint16_t len);
        bool write(uint16_t address, uint8_t * data, uint16_t len);

    private:

        I2C & _i2c;

        bool acquireBus();
        void releaseBus(); 

        uint32_t          _clkSpeed;
        uint32_t          _addressMode;
        uint32_t          _timeout;
};

#endif

