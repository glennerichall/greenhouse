#include <Arduino.h>
#include "greenhouse.h"
#include "pin_interrupt.h"
#include "timer.h"

greenhouse gh;
#include <avr/sleep.h>

void setup() {
    ITimer1.init();
    Serial.begin(115200, SERIAL_8N1);
    // gh.initialize();

    timer::init();
    PinInterrupt<8>::begin();
}

template<>
void PinInterrupt<8>::handle() {
    Serial.println("Button pressed");
}

void loop() {
    if (!timer::loop()) {
        sleep_mode();
    }


    // set_sleep_mode(SLEEP_MODE_IDLE);
    // sleep_mode();     // sleeps until timer or button wakes it
}
