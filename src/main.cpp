#include <Arduino.h>
#include "greenhouse.h"
#include "pin_interrupt.h"

greenhouse gh;
#include <avr/sleep.h>

void setup() {
    ITimer1.init();
    Serial.begin(115200, SERIAL_8N1);
    gh.initialize();

    PinInterrupt<4>::begin();
}

template<>
void PinInterrupt<4>::handle() {
    Serial.println("Button pressed");
}

void loop() {
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_mode();     // sleeps until timer or button wakes it
    sleep_disable();  // disables sleep until next call
}
