#include "i2c.hpp"

#ifdef I2C_USE_I2C1
// Table of I2C GPIO Pin Properties
static const I2C_GpioPins I2C1_PinPack[] = {
     /* Port_SCL,SCL,Port_SDA,SDA,      MODE      ,    SPEED     ,        AF */ 
    { GPIOB,GPIO_PIN_6,GPIOB,GPIO_PIN_7,GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C1 },
    { GPIOB,GPIO_PIN_8,GPIOB,GPIO_PIN_9,GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C1 },
};
#endif

#ifdef I2C_USE_I2C2
static const I2C_GpioPins I2C2_PinPack[] = {
    { GPIOB,GPIO_PIN_10,GPIOB,GPIO_PIN_11,GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C2 },
    { GPIOF,GPIO_PIN_1, GPIOF,GPIO_PIN_0, GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C2 },
    { GPIOH,GPIO_PIN_4, GPIOH,GPIO_PIN_5, GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C2 },
};
#endif

#ifdef I2C_USE_I2C3
static const I2C_GpioPins I2C3_PinPack[] = {
    { GPIOA,GPIO_PIN_8,GPIOC,GPIO_PIN_9, GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C3 },
    { GPIOH,GPIO_PIN_7,GPIOH,GPIO_PIN_8, GPIO_MODE_AF_OD,GPIO_SPEED_LOW, GPIO_AF4_I2C3 },
};
#endif


// Global instances of I2C 
I2C I2C_1(I2C1, DEF_I2C1_PINPACK, DEF_I2C1_SPEED);
I2C I2C_2(I2C2, DEF_I2C2_PINPACK, DEF_I2C2_SPEED);


I2C::I2C(I2C_TypeDef * i2c, 
    I2C_PinsPack pinpack, 
    uint32_t clkSpeed,
    uint32_t addressMode,
    uint32_t stretchMode)
    : _pinspack(pinpack),
      _hMutex(NULL)
{
    _hi2c.Instance = i2c;
    _hi2c.Init.ClockSpeed = clkSpeed;
    _hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    _hi2c.Init.OwnAddress1 = 0;
    _hi2c.Init.AddressingMode = addressMode;
    _hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    _hi2c.Init.OwnAddress2 = 0;
    _hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    _hi2c.Init.NoStretchMode = stretchMode;
}

HAL_StatusTypeDef I2C::initGPIO(I2C_GpioPins * gpiopins)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Initialize SCL
    GPIO_InitStruct.Pin = gpiopins->Scl;
    GPIO_InitStruct.Mode = gpiopins->Mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = gpiopins->Speed;
    GPIO_InitStruct.Alternate = gpiopins->AF;
    HAL_GPIO_Init(gpiopins->Scl_Port, &GPIO_InitStruct);
    // Initialize Sda
    GPIO_InitStruct.Pin = gpiopins->Sda;
    GPIO_InitStruct.Mode = gpiopins->Mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = gpiopins->Speed;
    GPIO_InitStruct.Alternate = gpiopins->AF;
    HAL_GPIO_Init(gpiopins->Sda_Port, &GPIO_InitStruct);

    return HAL_OK;

}

bool I2C::init()
{
    uint32_t freqrange = 0;
    uint32_t pclk1 = 0;

    // Create the mutex
    _hMutex = osMutexCreate(osMutex(MutexI2C));
    if (_hMutex == NULL) return false;


    // Initialize GPIO
    if (_hi2c.State == HAL_I2C_STATE_RESET)
    {
#ifdef I2C_USE_I2C1
        if (_hi2c.Instance == I2C1)
        {
            __I2C1_CLK_ENABLE();
            // Use the I2C1_Pin_Pack
            initGPIO((I2C_GpioPins *) &I2C1_PinPack[_pinspack]);
        }
#endif
#ifdef I2C_USE_I2C2
        if (_hi2c.Instance == I2C2)
        {
            __I2C2_CLK_ENABLE();
            initGPIO((I2C_GpioPins *) &I2C2_PinPack[_pinspack]);
        }
#endif
#ifdef I2C_USE_I2C3
        if (_hi2c.Instance == I2C3)
        {
            __I2C3_CLK_ENABLE();
            initGPIO((I2C_GpioPins *) &I2C3_PinPack[_pinspack]);
        }
#endif
    }

    /* Disble the selected I2C peripheral */
    __HAL_I2C_DISABLE(&_hi2c);

    /* Get PCLK1 frequency */
    pclk1 = HAL_RCC_GetPCLK1Freq();

    /* Calculate frequency range */
    freqrange = __HAL_I2C_FREQRANGE(pclk1);

    /*---------------------------- I2Cx CR2 Configuration ----------------------*/
    /* Configure I2Cx: Frequency range */
    _hi2c.Instance->CR2 = freqrange;

    /*---------------------------- I2Cx TRISE Configuration --------------------*/
    /* Configure I2Cx: Rise Time */
    _hi2c.Instance->TRISE = __HAL_I2C_RISE_TIME(freqrange, _hi2c.Init.ClockSpeed);

    /*---------------------------- I2Cx CCR Configuration ----------------------*/
    /* Configure I2Cx: Speed */
    _hi2c.Instance->CCR = __HAL_I2C_SPEED(pclk1, _hi2c.Init.ClockSpeed, _hi2c.Init.DutyCycle);

    /*---------------------------- I2Cx CR1 Configuration ----------------------*/
    /* Configure I2Cx: Generalcall and NoStretch mode */
    _hi2c.Instance->CR1 = (_hi2c.Init.GeneralCallMode | _hi2c.Init.NoStretchMode);

    /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
    /* Configure I2Cx: Own Address1 and addressing mode */
    _hi2c.Instance->OAR1 = (_hi2c.Init.AddressingMode | _hi2c.Init.OwnAddress1);

    /*---------------------------- I2Cx OAR2 Configuration ---------------------*/
    /* Configure I2Cx: Dual mode and Own Address2 */
    _hi2c.Instance->OAR2 = (_hi2c.Init.DualAddressMode | _hi2c.Init.OwnAddress2);

    /* Enable the selected I2C peripheral */
    __HAL_I2C_ENABLE(&_hi2c);

    _hi2c.ErrorCode = HAL_I2C_ERROR_NONE;
    _hi2c.State = HAL_I2C_STATE_READY;

    return true;
}

bool I2C::lock(uint32_t timeout)
{
    if ( _hMutex &&  osMutexWait( _hMutex , timeout ) == osOK)
        return true;

    return false;
}

bool I2C::unlock()
{
    if (_hMutex && osMutexRelease( _hMutex ) == osOK)
        return true;
    
    return false;
}

// These functions are just wrappers to HAL Driver functions
HAL_StatusTypeDef I2C::read(uint16_t address, uint8_t * data, uint16_t len, uint32_t timeout)
{
    return HAL_I2C_Master_Receive(&_hi2c, address, data, len, timeout);
}

HAL_StatusTypeDef I2C::write(uint16_t address, uint8_t * data, uint16_t len, uint32_t timeout)
{
    return HAL_I2C_Master_Transmit(&_hi2c, address, data, len, timeout);
}



