#ifndef __SPI_HPP__
#define __SPI_HPP__

/**
 * Author : Cola Vergil
 * Email  : vpcola@gmail.com
 * Date : Tue Jan 13 2015
 **/
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SPI_USE_SPI1
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;
#endif

#ifdef SPI_USE_SPI2
extern SPI_HandleTypeDef hspi2;
extern DMA_HandleTypeDef hdma_spi2_rx;
extern DMA_HandleTypeDef hdma_spi2_tx;
#endif

#ifdef SPI_USE_SPI3
extern SPI_HandleTypeDef hspi3;
extern DMA_HandleTypeDef hdma_spi3_rx;
extern DMA_HandleTypeDef hdma_spi3_tx;
#endif


#ifdef __cplusplus
}
#endif



typedef struct {
    GPIO_TypeDef  * SCK_Port;   // Port for SCK
    uint32_t    Sck;
    GPIO_TypeDef  * MISO_Port;  // Port for Miso
    uint32_t    Miso;
    GPIO_TypeDef  * MOSI_Port;  // Port for Mosi
    uint32_t    Mosi;
    uint32_t    AF;
} SPI_GpioPins;

typedef enum {
    SPI_PINPACK_0,
    SPI_PINPACK_1,
    SPI_PINPACK_2
} SPI_PinsPack;

// SPI1 Mappings
//                    SCK      MISO    MOSI     AF
// SPI_PINPACK_0 =    PA5      PA6     PA7      GPIO_AF5_SPI1
// SPI_PINPACK_1 =    PB3      PB4     PB5      GPIO_AF5_SPI1
// SPI_PINPACK_2 =    -

// SPI2 Mappings
// SPI_PINPACK_0 =    PB10     PC2     PC3      GPIO_AF5_SPI2
// SPI_PINPACK_1 =    PB13     PB14    PB15     GPIO_AF5_SPI2
// SPI_PINPACK_2 =    PI1      PI2     PI3      GPIO_AF5_SPI2
// SPI_PINPACK_3 =    -

// SPI3 Mappings
// SPI_PINPACK_0 =    PB3      PB4     PB5      GPIO_AF6_SPI3
// SPI_PINPACK_1 =    PC10     PC11    PC12     GPIO_AF6_SPI3
// SPI_PINPACK_2 =    -

typedef struct {
    uint32_t polarity;  // CPOL
    uint32_t phase;     // CPHA
} SPI_ModeType;

typedef enum {
    SPI_MODE_0,     // CPOL = SPI_POLARITY_LOW, CPHA = SPI_PHASE_1EDGE  
    SPI_MODE_1,     // CPOL = SPI_POLARITY_LOW, CPHA = SPI_PHASE_2EDGE 
    SPI_MODE_2,     // CPOL = SPI_POLARITY_HIGH, CPHA = SPI_PHASE_1EDGE
    SPI_MODE_3      // CPOL = SPI_POLARITY_HIGH, CPHA = SPI_PHASE_2EDGE
} SPI_Mode;

// Dma and dma channel configuration
typedef struct
{
    DMA_Stream_TypeDef * rxstream;    // rx stream
    uint32_t             rxchannel;
    DMA_Stream_TypeDef * txstream;    // tx stream
    uint32_t             txchannel;
} DMA_StreamMap;

typedef enum {
    DMA_STREAM_0,
    DMA_STREAM_1
} DMA_Stream;


// NOTE:
// SPI1 is driven by APB2 clock which runs at 84MHz
// SPI2 and SPI3 is driven by APB1 clock which runs at 42 MHz
// 
// SPI1 Frequency Map
// SPI_BAUDRATEPRESCALER_2 = 42MHz
// SPI_BAUDRATEPRESCALER_4 = 21MHz
// SPI_BAUDRATEPRESCALER_8 = 10.5MHz
// SPI_BAUDRATEPRESCALER_16 = 5.25MHz
// SPI_BAUDRATEPRESCALER_32 = 2.625MHz
// SPI_BAUDRATEPRESCALER_64 = 1.3125MHz
// SPI_BAUDRATEPRESCALER_128 = 656.25KHz
// SPI_BAUDRATEPRESCALER_256 = 328.125KHz

// SPI2 and SPI3 Frequency Map
// SPI_BAUDRATEPRESCALER_2 = 21MHz
// SPI_BAUDRATEPRESCALER_4 = 10.5MHz
// SPI_BAUDRATEPRESCALER_8 = 5.25MHz
// SPI_BAUDRATEPRESCALER_16 = 2.625MHz
// SPI_BAUDRATEPRESCALER_32 = 1.3125MHz
// SPI_BAUDRATEPRESCALER_64 = 656.25KHz
// SPI_BAUDRATEPRESCALER_128 = 328.125KHz
// SPI_BAUDRATEPRESCALER_256 = 164KHz

class SPI {
	public:
	
	SPI(SPI_TypeDef  * spi,
      SPI_PinsPack pinspack,
      SPI_Mode mode,
      uint32_t datasize = SPI_DATASIZE_8BIT,
      uint32_t baudrateprescaler = SPI_BAUDRATEPRESCALER_2
      );


    bool init();

    HAL_StatusTypeDef setDMAOptions(uint32_t direction,
            uint32_t pdataAlignment,
            uint32_t mdataAlignment );


    private:
    HAL_StatusTypeDef initGPIO(SPI_GpioPins * gpiopins);
    HAL_StatusTypeDef initDMA(DMA_StreamMap * streamMap,
            uint32_t periphInc,
            uint32_t memInc,
            uint32_t periphDataAlignment,
            uint32_t memoryDataAlignment);



    SPI_HandleTypeDef & _hspi;

    SPI_PinsPack      _pinspack;
    SPI_Mode          _mode;
    uint32_t          _datasize;
    uint32_t          _baudprescaler;

    DMA_HandleTypeDef & _hdma_rx;
    DMA_HandleTypeDef & _hdma_tx;
};

// Global instances of SPI 
#ifdef SPI_USE_SPI1
extern SPI SPI_1;
#endif

#ifdef SPI_USE_SPI2
extern SPI SPI_2;
#endif

#ifdef SPI_USE_SPI3
extern SPI SPI_3;
#endif


#endif

