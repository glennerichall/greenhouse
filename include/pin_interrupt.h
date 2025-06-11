#pragma once
#include <EnableInterrupt.h>
#include <timer.h>

// // Select the timers you're using, here ITimer1
// #define USE_TIMER_1     true
// #define USE_TIMER_2     false
// #define USE_TIMER_3     false
// #define USE_TIMER_4     false
// #define USE_TIMER_5     false
//
// #include <TimerInterrupt.h>
// #include <ISR_Timer.h>
//
// ISR_Timer timer;

#include <etl/platform.h>

template<uint8_t pin, decltype(LOW) active_state = LOW>
unsigned long active_duration() {
    static volatile unsigned long last_time = 0;
    auto state = digitalRead(pin);

    if (state == active_state) {
        return millis() - last_time;
    } else {
        last_time = millis();
    }
    return 0;
}


template<uint8_t pin>
class PinInterrupt {
public:
    static void begin(unsigned long holdDuration = 1000) {
        duration = holdDuration;
        pinMode(pin, INPUT_PULLUP);
        enableInterrupt(pin, isr, CHANGE);
    }

    static void handle(); // user-defined per-pin behavior

private:
    static volatile unsigned long duration;
    static volatile  timeout_id;

    static void isr() {
        bool state = digitalRead(pin);
        active_duration<pin>();

        if (state == LOW) {
            timeout_id = timer::set_timeout_sync(onTimeout, duration);
            Serial.println("starting timeout");
        } else {
            timer::remove_timeout_sync(timeout_id);
        }
    }

    static void onTimeout() {
        Serial.println("onTimeout");
        // Check pin still LOW before handling
        if (digitalRead(pin) == LOW) {
            handle();
        }
        timer_active = false;
    }
};


template<uint8_t pin>
volatile unsigned long PinInterrupt<pin>::duration;

template<uint8_t pin>
volatile bool PinInterrupt<pin>::timer_active = false;
