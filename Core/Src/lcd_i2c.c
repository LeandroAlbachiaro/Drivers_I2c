/*
 * lcd_i2c.c
 *
 *  Created on: Oct 8, 2025
 *      Author: leandro
 */


#include "lcd_i2c.h"
#include "main.h"

const uint8_t ROW_20[] = {0x00, 0x40, 0x14, 0x54};

/********** Helper: enviar nibble por I2C **********/
static void lcd_write_nibble(Lcd_I2C_HandleTypeDef *lcd, uint8_t nibble, uint8_t rs)
{
    uint8_t data = 0x00;

    // D4-D7 → P4-P7
    data |= (nibble & 0x0F) << 4;

    // RS → P0
    if(rs)
        data |= (1 << 0);
    else
        data &= ~(1 << 0);

    // R/W → P1 (siempre 0 = write)
    data &= ~(1 << 1);

    // Backlight → P3
    if(lcd->backlight)
        data |= (1 << 3);
    else
        data &= ~(1 << 3);

    // Pulso EN → P2
    data |= (1 << 2);        // EN = 1
    PCF8574_Write(data, PCF8574_DISPLAY_ADDR);
    DELAY(1);
    data &= ~(1 << 2);       // EN = 0
    PCF8574_Write(data, PCF8574_DISPLAY_ADDR);
    DELAY(1);
}

/********** Enviar byte completo **********/
static void lcd_write_byte(Lcd_I2C_HandleTypeDef *lcd, uint8_t byte, uint8_t rs)
{
    lcd_write_nibble(lcd, byte >> 4, rs);    // Nibble alto
    lcd_write_nibble(lcd, byte & 0x0F, rs);  // Nibble bajo
}

/********** Comando y datos **********/
static void lcd_write_command(Lcd_I2C_HandleTypeDef *lcd, uint8_t cmd)
{
    lcd_write_byte(lcd, cmd, 0);
}

static void lcd_write_data(Lcd_I2C_HandleTypeDef *lcd, uint8_t data)
{
    lcd_write_byte(lcd, data, 1);
}

/********** Public functions **********/
void Lcd_I2C_Init(Lcd_I2C_HandleTypeDef *lcd)
{
    DELAY(50); // Espera power on

    lcd_write_nibble(lcd, 0x03, 0);
    DELAY(5);
    lcd_write_nibble(lcd, 0x03, 0);
    DELAY(5);
    lcd_write_nibble(lcd, 0x03, 0);
    DELAY(1);
    lcd_write_nibble(lcd, 0x02, 0); // 4-bit mode

    lcd_write_command(lcd, FUNCTION_SET | OPT_N);   // 4-bit, 2 líneas
    lcd_write_command(lcd, DISPLAY_ON_OFF | OPT_D); // Display on
    lcd_write_command(lcd, CLEAR_DISPLAY);
    lcd_write_command(lcd, ENTRY_MODE_SET | OPT_INC);
}

void Lcd_I2C_Clear(Lcd_I2C_HandleTypeDef *lcd)
{
    lcd_write_command(lcd, CLEAR_DISPLAY);
    DELAY(2);
}

void Lcd_I2C_SetCursor(Lcd_I2C_HandleTypeDef *lcd, uint8_t row, uint8_t col)
{
#ifdef LCD20xN
    lcd_write_command(lcd, SET_DDRAM_ADDR + ROW_20[row] + col);
#endif
}

void Lcd_I2C_Print(Lcd_I2C_HandleTypeDef *lcd, char *str)
{
    for(uint8_t i=0; i<strlen(str); i++)
    {
        lcd_write_data(lcd, str[i]);
    }
}

void Lcd_I2C_PrintInt(Lcd_I2C_HandleTypeDef *lcd, int number)
{
    char buffer[12];
    sprintf(buffer, "%d", number);
    Lcd_I2C_Print(lcd, buffer);
}

void Lcd_I2C_DefineChar(Lcd_I2C_HandleTypeDef *lcd, uint8_t code, uint8_t bitmap[])
{
    lcd_write_command(lcd, SETCGRAM_ADDR + (code << 3));
    for(uint8_t i=0; i<8; i++)
        lcd_write_data(lcd, bitmap[i]);
}

/*HAL_StatusTypeDef PCF8574_Write(uint8_t data)
{
    return HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, &data, 1, HAL_MAX_DELAY);
}*/
