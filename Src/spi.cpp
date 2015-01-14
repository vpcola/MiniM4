#include "spi.hpp"

// SPI1 Mappings
//                    SCK      MISO    MOSI     AF
// SPI_PINPACK_0 =    PA5      PA6     PA7      GPIO_AF5_SPI1
// SPI_PINPACK_1 =    PB3      PB4     PB5      GPIO_AF5_SPI1
// SPI_PINPACK_2 =    -

static const SPI_GpioPins spi1pins[] = 
{
    // SCK Port, SCK,        MISO Port, MISO,       MOSI Port, MOSI,       AF 
    {  GPIOA,    GPIO_PIN_5, GPIOA,     GPIO_PIN_6, GPIOA,     GPIO_PIN_7, GPIO_AF5_SPI1 },
    {  GPIOB,    GPIO_PIN_3, GPIOB,     GPIO_PIN_4, GPIOB,     GPIO_PIN_5, GPIO_AF5_SPI1 }
};

// SPI2 Mappings
// SPI_PINPACK_0 =    PB10     PC2     PC3      GPIO_AF5_SPI2
// SPI_PINPACK_1 =    PB13     PB14    PB15     GPIO_AF5_SPI2
// SPI_PINPACK_2 =    PI1      PI2     PI3      GPIO_AF5_SPI2
// SPI_PINPACK_3 =    -

static const SPI_GpioPins spi2pins[] =
{
    // SCK Port, SCK,         MISO Port, MISO,        MOSI Port, MOSI,        AF 
    {  GPIOB,    GPIO_PIN_10, GPIOC,     GPIO_PIN_2,  GPIOC,     GPIO_PIN_3,  GPIO_AF5_SPI2 },
    {  GPIOB,    GPIO_PIN_13, GPIOB,     GPIO_PIN_14, GPIOB,     GPIO_PIN_15, GPIO_AF5_SPI2 },
    {  GPIOI,    GPIO_PIN_1,  GPIOI,     GPIO_PIN_2,  GPIOI,     GPIO_PIN_3,  GPIO_AF5_SPI2 }
};

// SPI3 Mappings
// SPI_PINPACK_0 =    PB3      PB4     PB5      GPIO_AF6_SPI3
// SPI_PINPACK_1 =    PC10     PC11    PC12     GPIO_AF6_SPI3
// SPI_PINPACK_2 =    -

static const SPI_GpioPins spi3pins[] = 
{
    // SCK Port, SCK,         MISO Port, MISO,        MOSI Port, MOSI,        AF 
    { GPIOB,     GPIO_PIN_3,  GPIOB,     GPIO_PIN_4,  GPIOB,     GPIO_PIN_5,  GPIO_AF6_SPI3 },
    { GPIOC,     GPIO_PIN_10, GPIOC,     GPIO_PIN_11, GPIOC,     GPIO_PIN_12, GPIO_AF6_SPI3 }
};


static const SPI_ModeType spiModeType[] = 
{
    { SPI_POLARITY_LOW , SPI_PHASE_1EDGE },
    { SPI_POLARITY_LOW , SPI_PHASE_2EDGE },
    { SPI_POLARITY_HIGH, SPI_PHASE_1EDGE },
    { SPI_POLARITY_HIGH, SPI_PHASE_2EDGE }
};

static const DMA_StreamMap spi1StreamMap[] = 
{
    // rxstream, rxchannel, txstream, txchannel 
    { DMA2_Stream0, DMA_CHANNEL_3, DMA2_Stream3, DMA_CHANNEL_3 },
    { DMA2_Stream2, DMA_CHANNEL_3, DMA2_Stream5, DMA_CHANNEL_3 }
};

static const DMA_StreamMap spi2StreamMap[] =
{
    { DMA1_Stream3, DMA_CHANNEL_0, DMA1_Stream4, DMA_CHANNEL_0 },
};

static const DMA_StreamMap spi3StreamMap[] = 
{
    { DMA1_Stream0, DMA_CHANNEL_0, DMA1_Stream5, DMA_CHANNEL_0 },
    { DMA1_Stream2, DMA_CHANNEL_0, DMA1_Stream7, DMA_CHANNEL_0 }
};

// Static instances of the handles 
// used in the C functions of the HAL driver
#ifdef SPI_USE_SPI1
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

SPI SPI_1(SPI1, SPI_1_DEFAULT_PINPACK, SPI_1_DEFAULT_MODE);
#endif

#ifdef SPI_USE_SPI2
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi2_tx;

SPI SPI_2(SPI2, SPI_2_DEFAULT_PINPACK, SPI_1_DEFAULT_MODE);
#endif

#ifdef SPI_USE_SPI3
SPI_HandleTypeDef hspi3;
DMA_HandleTypeDef hdma_spi3_rx;
DMA_HandleTypeDef hdma_spi3_tx;

SPI SPI_3(SPI3, SPI_3_DEFAULT_PINPACK, SPI_3_DEFAULT_MODE);
#endif



DMA_HandleTypeDef * getDMATypeDef(SPI_TypeDef * spi, bool isRx)
{
#ifdef SPI_USE_SPI1
    if (spi == SPI1)
        return (isRx) ? &hdma_spi1_rx : &hdma_spi1_tx;
#endif

#ifdef SPI_USE_SPI2
    if (spi == SPI2)
        return (isRx) ? &hdma_spi2_rx : &hdma_spi2_tx;
#endif

#ifdef SPI_USE_SPI3
    if (spi == SPI3)
        return (isRx) ? &hdma_spi3_rx : &hdma_spi3_tx;
#endif

    return NULL;
}

SPI_HandleTypeDef * getSPITypeDef(SPI_TypeDef * spi)
{
#ifdef SPI_USE_SPI1
    if (spi == SPI1)
        return &hspi1;
#endif
#ifdef SPI_USE_SPI2
    if (spi == SPI2)
        return &hspi2;
#endif
#ifdef SPI_USE_SPI3
    if (spi == SPI3)
        return &hspi3;
#endif
    return NULL;
}



SPI::SPI(SPI_TypeDef  * spi,
    SPI_PinsPack pinspack,
    SPI_Mode mode,
    uint32_t datasize,
    uint32_t baudprescaler
    )
    // Select the correct ref to use for this class
    : _hspi(*(getSPITypeDef(spi))),
    _pinspack(pinspack),
    _mode(mode),
    _datasize(datasize),
    _baudprescaler(baudprescaler),
    _hdma_rx(*(getDMATypeDef(spi, true))),
    _hdma_tx(*(getDMATypeDef(spi, false)))
{
    // Initialize hspi parameters
    _hspi.Instance = spi;
    _hspi.Init.Mode = SPI_MODE_MASTER;
    _hspi.Init.Direction = SPI_DIRECTION_2LINES;
    _hspi.Init.DataSize = _datasize;
    _hspi.Init.CLKPolarity = spiModeType[_mode].polarity;
    _hspi.Init.CLKPhase = spiModeType[_mode].phase;
    _hspi.Init.NSS = SPI_NSS_SOFT;
    _hspi.Init.BaudRatePrescaler = _baudprescaler;
    _hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
    _hspi.Init.TIMode = SPI_TIMODE_DISABLED;
    _hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;

}

HAL_StatusTypeDef SPI::initGPIO(SPI_GpioPins * gpiopins)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Initialize SCK
    GPIO_InitStruct.Pin = gpiopins->Sck;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = gpiopins->AF;
    HAL_GPIO_Init(gpiopins->SCK_Port, &GPIO_InitStruct);

    // Initialize MISO
    GPIO_InitStruct.Pin = gpiopins->Miso;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = gpiopins->AF;
    HAL_GPIO_Init(gpiopins->MISO_Port, &GPIO_InitStruct);

    // Initialize MOSI
    GPIO_InitStruct.Pin = gpiopins->Mosi;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    GPIO_InitStruct.Alternate = gpiopins->AF;
    HAL_GPIO_Init(gpiopins->MOSI_Port, &GPIO_InitStruct);

    return HAL_OK;
}

HAL_StatusTypeDef SPI::setDMAOptions(
    uint32_t direction,
    uint32_t pdataAlignment,
    uint32_t mdataAlignment )
{
    DMA_HandleTypeDef & hdma = (direction == DMA_PERIPH_TO_MEMORY) ? _hdma_rx : _hdma_tx;

    hdma.Init.PeriphDataAlignment = pdataAlignment;
    hdma.Init.MemDataAlignment = mdataAlignment;

    // TODO: disable and re-initialize DMA?

    return HAL_OK;
}

HAL_StatusTypeDef SPI::initDMA(DMA_StreamMap * streamMap,
    uint32_t periphInc,
    uint32_t memInc,
    uint32_t periphDataAlignment,
    uint32_t memoryDataAlignment)
{
    _hdma_rx.Instance = streamMap->rxstream;
    _hdma_rx.Init.Channel = streamMap->rxchannel;
    _hdma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    _hdma_rx.Init.PeriphInc = periphInc;
    _hdma_rx.Init.MemInc = memInc;
    _hdma_rx.Init.PeriphDataAlignment = periphDataAlignment;
    _hdma_rx.Init.MemDataAlignment = memoryDataAlignment;
    _hdma_rx.Init.Mode = DMA_NORMAL;
    _hdma_rx.Init.Priority = DMA_PRIORITY_LOW;
    _hdma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&_hdma_rx);

    __HAL_LINKDMA(&_hspi,hdmarx,_hdma_rx);

    _hdma_tx.Instance = streamMap->txstream;
    _hdma_tx.Init.Channel = streamMap->rxchannel;
    _hdma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    _hdma_tx.Init.PeriphInc = periphInc;
    _hdma_tx.Init.MemInc = memInc;
    _hdma_tx.Init.PeriphDataAlignment = periphDataAlignment;
    _hdma_tx.Init.MemDataAlignment = memoryDataAlignment;
    _hdma_tx.Init.Mode = DMA_NORMAL;
    _hdma_tx.Init.Priority = DMA_PRIORITY_LOW;
    _hdma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&_hdma_tx);

    __HAL_LINKDMA( &_hspi,hdmatx,_hdma_tx);


    return HAL_OK;
}

bool SPI::init()
{
    /* Check the parameters */
    assert_param(IS_SPI_MODE(_hspi.Init.Mode));
    assert_param(IS_SPI_DIRECTION_MODE(_hspi.Init.Direction));
    assert_param(IS_SPI_DATASIZE(_hspi.Init.DataSize));
    assert_param(IS_SPI_CPOL(_hspi.Init.CLKPolarity));
    assert_param(IS_SPI_CPHA(_hspi.Init.CLKPhase));
    assert_param(IS_SPI_NSS(_hspi.Init.NSS));
    assert_param(IS_SPI_BAUDRATE_PRESCALER(_hspi.Init.BaudRatePrescaler));
    assert_param(IS_SPI_FIRST_BIT(_hspi.Init.FirstBit));
    assert_param(IS_SPI_TIMODE(_hspi.Init.TIMode));
    assert_param(IS_SPI_CRC_CALCULATION(_hspi.Init.CRCCalculation));
    assert_param(IS_SPI_CRC_POLYNOMIAL(_hspi.Init.CRCPolynomial));

    if(_hspi.State == HAL_SPI_STATE_RESET)
    {
        /* Init the low level hardware : GPIO, CLOCK, NVIC... */
        if (_hspi.Instance == SPI1 )
        {
            __SPI1_CLK_ENABLE();
            initGPIO((SPI_GpioPins *) &spi1pins[_pinspack]);
            initDMA((DMA_StreamMap *) &spi1StreamMap[0], 
                    DMA_PINC_DISABLE, DMA_MINC_ENABLE, 
                    DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE );

        }

        if (_hspi.Instance == SPI2 )
        {
            __SPI2_CLK_ENABLE();
            initGPIO((SPI_GpioPins *) &spi2pins[_pinspack]);
            initDMA((DMA_StreamMap *) &spi2StreamMap[0], 
                    DMA_PINC_DISABLE, DMA_MINC_ENABLE, 
                    DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE );
        }

        if (_hspi.Instance == SPI3 )
        {
            __SPI3_CLK_ENABLE();
            initGPIO((SPI_GpioPins *) &spi3pins[_pinspack]);
            initDMA((DMA_StreamMap *) &spi3StreamMap[0], 
                    DMA_PINC_DISABLE, DMA_MINC_ENABLE, 
                    DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE );
        }

    }

    _hspi.State = HAL_SPI_STATE_BUSY;

    /* Disble the selected SPI peripheral */
    __HAL_SPI_DISABLE(&_hspi);

    /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
    /* Configure : SPI Mode, Communication Mode, Data size, Clock polarity and phase, NSS management,
       Communication speed, First bit and CRC calculation state */
    _hspi.Instance->CR1 = (_hspi.Init.Mode | _hspi.Init.Direction | _hspi.Init.DataSize |
            _hspi.Init.CLKPolarity | _hspi.Init.CLKPhase | (_hspi.Init.NSS & SPI_CR1_SSM) |
            _hspi.Init.BaudRatePrescaler | _hspi.Init.FirstBit  | _hspi.Init.CRCCalculation);

    /* Configure : NSS management */
    _hspi.Instance->CR2 = (((_hspi.Init.NSS >> 16) & SPI_CR2_SSOE) | _hspi.Init.TIMode);

    /*---------------------------- SPIx CRCPOLY Configuration ------------------*/
    /* Configure : CRC Polynomial */
    _hspi.Instance->CRCPR = _hspi.Init.CRCPolynomial;

    /* Activate the SPI mode (Make sure that I2SMOD bit in I2SCFGR register is reset) */
    _hspi.Instance->I2SCFGR &= (uint32_t)(~SPI_I2SCFGR_I2SMOD);

    _hspi.ErrorCode = HAL_SPI_ERROR_NONE;
    _hspi.State = HAL_SPI_STATE_READY;

    return true;
}



