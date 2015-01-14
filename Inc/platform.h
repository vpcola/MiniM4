#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/**
 * Author : Cola Vergil
 * Email  : vpcola@gmail.com
 * Date : Mon Jan 12 2015
 **/


#define I2C_USE_I2C1    // I2C1 is ENABLED
#define I2C_USE_I2C2    // I2C2 is ENABLED
//#define I2C_USE_I2C3

#define I2C_DEFAULT_TIMEOUT 1000

#define DEF_I2C1_PINPACK I2C_PINPACK_2  // Pinspack 2 ( PB8, PB9 as SCL and SDA)
#define DEF_I2C2_PINPACK I2C_PINPACK_1  // Pinspack 1 ( PB10, PB11 as SCL and SDA)
#define DEF_I2C3_PINPACK I2C_PINPACK_1

#define DEF_I2C1_SPEED 100000
#define DEF_I2C2_SPEED 100000
#define DEF_I2C3_SPEED 100000

#define SPI_USE_SPI1
#define SPI_USE_SPI2
//#define SPI_USE_SPI3

#define SPI_1_DEFAULT_PINPACK   SPI_PINPACK_0
#define SPI_1_DEFAULT_MODE      SPI_MODE_0

#define SPI_2_DEFAULT_PINPACK   SPI_PINPACK_0
#define SPI_2_DEFAULT_MODE      SPI_MODE_0

#define SPI_3_DEFAULT_PINPACK   SPI_PINPACK_0
#define SPI_3_DEFAULT_MODE      SPI_MODE_0


#endif

