/*
 * mimico_i2c.c
 *
 *  Created on: Oct 8, 2025
 *      Author: leandro
 */

#include "mimico_i2c.h"
#include "main.h"

void mimico()
{
	PCF8574_Write(0b11111110, PCF8574_MIMICO_ADDR); // 0xFE -> PB0 en 0, Led encendido
	HAL_Delay(500);

	PCF8574_Write(0b11111101, PCF8574_MIMICO_ADDR);  //
	HAL_Delay(500);

	PCF8574_Write(0b11111011, PCF8574_MIMICO_ADDR);  //
	HAL_Delay(500);
}
