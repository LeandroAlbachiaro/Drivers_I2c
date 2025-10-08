/*
 * pcf8574.c
 *
 *  Created on: Oct 8, 2025
 *      Author: leandro
 */


#include "main.h"
#include "lcd_i2c.h"
#include "mimico_i2c.h"

HAL_StatusTypeDef PCF8574_Write(uint8_t data, uint8_t pcf_addr)
{
    return HAL_I2C_Master_Transmit(&hi2c1, pcf_addr, &data, 1, HAL_MAX_DELAY);
}
