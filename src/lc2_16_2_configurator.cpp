//
// Created by glenneric.hall on 08/05/2025.
//

#include <Arduino.h>

template<uint8_t pin, unsigned long duration = 3000>
bool is_active() {
    static unsigned long last_time = 0;
    static bool last_state = 0;

    auto elapsed = millis() - last_time;
    auto state = digitalRead(pin);

    if (state) {
        if (elapsed > duration) {
            return true;
        }
    } else {
        last_time = millis();
    }
    return false;
}

void lc2_16_2_configurator::sense() {

}