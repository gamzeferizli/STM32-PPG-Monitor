#include "lcd_i2c.h"

extern I2C_HandleTypeDef hi2c1;

// ---- DOĞRU PIN MAPPING (senin kartına göre) ----
// PCF8574 -> LCD
// P0 → RS
// P1 → RW
// P2 → EN
// P3 → BL (backlight)
// P4 → D4
// P5 → D5
// P6 → D6
// P7 → D7

#define PIN_RS   (1 << 0)
#define PIN_RW   (1 << 1)
#define PIN_EN   (1 << 2)
#define PIN_BL   (1 << 3)

static void lcd_send_internal(uint8_t data, uint8_t rs)
{
    uint8_t high = (data & 0xF0) >> 4;  // upper 4 bits
    uint8_t low  = data & 0x0F;         // lower 4 bits

    uint8_t high_out = (high << 4);    // P4-P7 = data
    uint8_t low_out  = (low  << 4);

    // RS ekle
    if (rs) {
        high_out |= PIN_RS;
        low_out  |= PIN_RS;
    }

    // Backlight
    high_out |= PIN_BL;
    low_out  |= PIN_BL;

    // EN darbeleri
    uint8_t seq[4] = {
        high_out | PIN_EN,
        high_out,
        low_out | PIN_EN,
        low_out
    };

    HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, seq, 4, HAL_MAX_DELAY);
}

static void lcd_send_cmd(uint8_t cmd)
{
    lcd_send_internal(cmd, 0);
}

static void lcd_send_data(uint8_t data)
{
    lcd_send_internal(data, 1);
}

void lcd_init(void)
{
    HAL_Delay(50);

    // Initialization sequence (datasheet'e uygun)
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);

    lcd_send_cmd(0x20); // 4-bit mode

    lcd_send_cmd(0x28); // 2-line mode, 5x8 font
    lcd_send_cmd(0x0C); // Display ON, cursor OFF
    lcd_send_cmd(0x06); // Auto-increment
    lcd_clear();
}

void lcd_clear(void)
{
    lcd_send_cmd(0x01);
    HAL_Delay(2);
}

void lcd_goto_xy(uint8_t col, uint8_t row)
{
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    lcd_send_cmd(addr);
}

void lcd_send_string(char *str)
{
    while (*str)
        lcd_send_data(*str++);
}
