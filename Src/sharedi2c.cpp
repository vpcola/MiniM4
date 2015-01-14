#include "sharedi2c.hpp"

SharedI2C::SharedI2C(I2C & i2c, 
    uint32_t clkSpeed,
    uint32_t addressMode,
    uint32_t timeout)
    : _i2c(i2c),
     _clkSpeed(clkSpeed),
     _addressMode(addressMode),
     _timeout(timeout)
{
}

bool SharedI2C::acquireBus()
{
    I2C_HandleTypeDef & hi2c = _i2c.getHandle();

    if (hi2c.State != HAL_I2C_STATE_READY)
        return false;

    if (_i2c.lock(1000))
    {
        // re-initialize i2c if other processes
        // changes the i2c parameters.
        if ((hi2c.Init.ClockSpeed != _clkSpeed) ||
            (hi2c.Init.AddressingMode != _addressMode))
        {
            hi2c.Init.ClockSpeed = _clkSpeed;
            hi2c.Init.AddressingMode = _addressMode;

            _i2c.init(); 
        }

        return true;
    }

    return false;
}

void SharedI2C::releaseBus()
{
    _i2c.unlock(); 
}

// These functions are just wrappers to HAL Driver functions
bool SharedI2C::read(uint16_t address, uint8_t * data, uint16_t len)
{
    bool retval = false;

    if ( acquireBus() )
    {
        retval =   _i2c.read(address, data, len, _timeout) == HAL_OK ;
        releaseBus();
    }

    return retval;
}

bool SharedI2C::write(uint16_t address, uint8_t * data, uint16_t len)
{
    bool retval = false;

    if ( acquireBus() )
    {
        retval =  _i2c.write(address, data, len, _timeout) == HAL_OK;
        releaseBus();
    }

    return retval;
}



