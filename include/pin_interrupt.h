#pragma once
#include <EnableInterrupt.h>

#define USE_TIMER_1     true

#include <TimerInterrupt.h>
#include <etl/platform.h>

template<uint8_t pin>
unsigned long active_duration() {
    static volatile unsigned long last_time = 0;
    auto state = digitalRead(pin);

    if (state) {
       return millis() - last_time;
    } else {
        last_time = millis();
    }
    return 0;
}


template<uint8_t pin>
class PinInterrupt {
public:
    static void begin(unsigned long holdDuration = 3000) {
        duration = holdDuration;
        timerActive = false;
        pinMode(pin, INPUT_PULLUP);
        enableInterrupt(pin, isr, CHANGE);
        ITimer.init();
    }

    static void handle(); // user-defined per-pin behavior

private:
    static volatile unsigned long duration;
    static volatile bool timerActive;
    static TimerInterrupt ITimer;

    static void isr() {
        bool state = digitalRead(pin);

        active_duration<pin>();

        if (state) {
            // Pin HIGH → start timer
            if (!timerActive) {
                ITimer.attachInterruptInterval(duration * 1000UL, onTimeout);
                timerActive = true;
            }
        } else {
            // Pin LOW → cancel timer
            ITimer.detachInterrupt();
            timerActive = false;
        }
    }

    static void onTimeout() {
        // Check pin still HIGH before handling
        if (digitalRead(pin)) {
            handle();
        }
        timerActive = false;
    }
};

template<uint8_t pin>
TimerInterrupt PinInterrupt<pin>::ITimer;

template<uint8_t pin>
volatile unsigned long PinInterrupt<pin>::duration;

template<uint8_t pin>
volatile bool PinInterrupt<pin>::timerActive;
