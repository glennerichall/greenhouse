//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_LCD_DISPLAY_H
#define GREENHOUSE_LCD_DISPLAY_H

#include <display.h>
#include <LiquidCrystal.h>

template<uint8_t cols, uint8_t rows,
        uint8_t rs, uint8_t enable,
        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7>
struct lcd_display : display {
private:
    LiquidCrystal lcd;

    void print_line(const char *text, int line) {
        lcd.setCursor(0, line);         // Move to second line
        lcd.print("                ");  // Clear previous reading
        lcd.setCursor(0, line);         // Reset cursor again
        lcd.print(text);                // Print the new reading
    }

public:
    lcd_display() : lcd(rs, enable, d4, d5, d6, d7) {
    }

    void initialize() override {
        lcd.begin(cols, rows);
    }
};

template<uint8_t rs, uint8_t enable,
        uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7>
using lcd_16_2 = lcd_display<16, 2, rs, enable, d4, d5, d6, d7>;


#endif //GREENHOUSE_LCD_DISPLAY_H
