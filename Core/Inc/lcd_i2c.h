#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f1xx_hal.h"

#define LCD_I2C_ADDR (0x27 << 1)

void lcd_init(void);
void lcd_clear(void);
void lcd_goto_xy(uint8_t col, uint8_t row);
void lcd_send_string(char *str);

#endif
