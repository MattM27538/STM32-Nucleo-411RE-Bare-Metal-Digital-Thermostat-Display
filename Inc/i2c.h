
#ifndef __i2c_H
#define __i2c_H

#include "stm32f4xx.h"
#include <stdint.h>

void i2cInit();

void i2cWriteByte(const uint8_t controllerAddress, const uint8_t targetAddress, const uint8_t data);

void i2cWriteMultipleBytes(const uint8_t controllerAddress, const uint8_t targetAddress, const char *dataBuffer, const uint16_t dataBufferLength);

#endif

