#ifndef __I2C_H__
#define __I2C_H__

/**
 * Author : Cola Vergil
 * Email  : vpcola@gmail.com
 * Date : Thu Jan 08 2015
 **/

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "platform.h"


typedef enum {
    I2C_PINPACK_1,
    I2C_PINPACK_2,
    I2C_PINPACK_3
} I2C_PinsPack;


typedef struct {
    GPIO_TypeDef  * Scl_Port;    // Port for SCL
    uint32_t    Scl;
    GPIO_TypeDef  * Sda_Port;    // Port for SDA
    uint32_t    Sda;
    uint32_t    Mode;    // Same mode for scl,sda 
    uint32_t    Speed;   // Same speed for scl, sda
    uint32_t    AF; 
} I2C_GpioPins;


osMutexDef (MutexI2C);

class I2C {

    public:
        I2C(I2C_TypeDef * i2c, 
            I2C_PinsPack pinpack, 
            uint32_t clkSpeed,
            uint32_t addressMode = I2C_ADDRESSINGMODE_7BIT,
            uint32_t stretchMode = I2C_NOSTRETCH_DISABLED
            );

        bool init();

        I2C_HandleTypeDef & getHandle() { return _hi2c; }

        bool lock(uint32_t timeout);
        bool unlock();

        HAL_StatusTypeDef read(uint16_t address, uint8_t * data, uint16_t len, uint32_t timeout);
        HAL_StatusTypeDef write(uint16_t address, uint8_t * data, uint16_t len, uint32_t timeout);

    private:
        HAL_StatusTypeDef initGPIO(I2C_GpioPins * gpiopins);

        I2C_HandleTypeDef _hi2c;
        I2C_PinsPack      _pinspack;

        osMutexId         _hMutex;
};

// Global declarations of I2C instances
extern I2C I2C_1;
extern I2C I2C_2;


#endif

