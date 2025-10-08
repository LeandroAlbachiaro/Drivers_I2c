/*
 * mimico_i2c.h
 *
 *  Created on: Oct 8, 2025
 *      Author: leandro
 */

#ifndef INC_MIMICO_I2C_H_
#define INC_MIMICO_I2C_H_

#include "stm32f7xx_hal.h"

#define PCF8574_MIMICO_ADDR 0x26 << 1  // desplazamiento por HAL que usa 8 bits
extern I2C_HandleTypeDef hi2c1;

void mimico();

#endif /* INC_MIMICO_I2C_H_ */
