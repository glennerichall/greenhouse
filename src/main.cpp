#include <Arduino.h>
#include <LiquidCrystal.h>
#include <simple_bang_bang.h>

#include "controller_composite.h"

#define D0 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D8 8
#define D9 9
#define D10 10
#define D11 11
#define D12 12
#define D13 13
#define D14 14
#define D15 15


// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(D12, D11, D5, D4, D3, D2);

using humidity = heater_bang_bang<A0, D6>;
using light = heater_bang_bang<A1, D7>;

controller_composite<
        humidity,
        light
> controllers;

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    lcd.begin(16, 2); // 16 columns, 2 rows
    lcd.print("Analog Value:");

    controllers.at<humidity>().initialize(
            "Humidity", 50, 100);

    controllers.at<light>().initialize(
            "Humidity", 50, 100);


}

template<typename T>
void print_line(T text, int line) {
    lcd.setCursor(0, line);         // Move to second line
    lcd.print("                ");  // Clear previous reading
    lcd.setCursor(0, line);         // Reset cursor again
    lcd.print(text);                // Print the new reading
}

void print_title(const char *title) {
    print_line(title, 0);
}

template<typename T>
void print_value(T value) {
    print_line(value, 1);
}

void loop() {
    controllers.update();
    delay(1000);
}
