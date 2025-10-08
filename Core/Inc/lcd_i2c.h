/*
 * lcd_i2c.h
 *
 *  Created on: Oct 8, 2025
 *      Author: leandro
 */

#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "stm32f7xx_hal.h"
#include "string.h"
#include "stdio.h"

/********** PCF8574 Mapping **********
 * P0 → RS
 * P1 → R/W (siempre 0)
 * P2 → EN
 * P3 → Backlight
 * P4 → D4
 * P5 → D5
 * P6 → D6
 * P7 → D7
 *************************************/

#define LCD20xN
extern const uint8_t ROW_20[];
#define PCF8574_DISPLAY_ADDR 0x27 << 1  // desplazamiento por HAL que usa 8 bits
extern I2C_HandleTypeDef hi2c1;


/********** Commands **********/
#define CLEAR_DISPLAY        0x01
#define RETURN_HOME          0x02
#define ENTRY_MODE_SET       0x04
#define OPT_INC              0x02
#define DISPLAY_ON_OFF       0x08
#define OPT_D                0x04
#define OPT_C                0x02
#define OPT_B                0x01
#define FUNCTION_SET         0x20
#define OPT_N                0x08
#define SET_DDRAM_ADDR       0x80
#define SETCGRAM_ADDR        0x40

#define DELAY(X) HAL_Delay(X)

/********** I2C LCD Handle **********/
typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t pcf_addr;    // Dirección del PCF8574 (shifted)
    uint8_t backlight;   // 1 para encender backlight
} Lcd_I2C_HandleTypeDef;

/********** Public functions **********/
void Lcd_I2C_Init(Lcd_I2C_HandleTypeDef *lcd);
void Lcd_I2C_Clear(Lcd_I2C_HandleTypeDef *lcd);
void Lcd_I2C_SetCursor(Lcd_I2C_HandleTypeDef *lcd, uint8_t row, uint8_t col);
void Lcd_I2C_Print(Lcd_I2C_HandleTypeDef *lcd, char *str);
void Lcd_I2C_PrintInt(Lcd_I2C_HandleTypeDef *lcd, int number);
void Lcd_I2C_DefineChar(Lcd_I2C_HandleTypeDef *lcd, uint8_t code, uint8_t bitmap[]);


#endif /* LCD_I2C_H_ */
