#include <Arduino.h>
#include <LiquidCrystal.h>
#include <simple_bang_bang.h>

#include "greenhouse.h"

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define analog input pin
const int humidityPin = A0;
const int photoPin = A1;

#define D6 6

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    lcd.begin(16, 2); // 16 columns, 2 rows
    lcd.print("Analog Value:");

    // pinMode(motorPin, OUTPUT);
}

template<typename T>
void print_line(T text, int line) {
    lcd.setCursor(0, line); // Move to second line
    lcd.print("                "); // Clear previous reading
    lcd.setCursor(0, line); // Reset cursor again
    lcd.print(text); // Print the new reading
}

void print_title(const char *title) {
    print_line(title, 0);
}

template<typename T>
void print_value(T value) {
    print_line(value, 1);
}




using humidity  = simple_bang_bang<A0, D6, true>;
using light  = simple_bang_bang<A0, D6, true>;

greenhouse<humidity> gh;

void loop() {
    // hum.update();

    print_title("Humidity:");

    delay(1000);

    int photoValue = analogRead(photoPin);
    print_title("Lighting:");
    print_value(photoValue);

    Serial.print("lighting :");
    Serial.println(photoValue);


    delay(1000);
}
