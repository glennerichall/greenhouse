//
// Created by glenn on 05/05/25.
//

#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <etl/error_handler.h>
#include "controller.h"

#define HEATER true
#define COOLER false

template<bool type>
struct bang_bang_behavior;

template<>
struct bang_bang_behavior<HEATER> {
    static bool isBelow(int value, int low) { return value < low; }

    static bool isAbove(int value, int high) { return value > high; }
};

template<>
struct bang_bang_behavior<COOLER> {
    static bool isBelow(int value, int low) { return value > low; /* ie -value < -low */}

    static bool isAbove(int value, int high) { return value < high; }
};


template<
        uint8_t inport,
        uint8_t outport,
        bool type = HEATER
>
struct simple_bang_bang : controller {
private:
    int value{};
    int state{LOW};
    int high{0}, low{0};
    const char *name{""};
    bool initialized{false};

    using behavior = bang_bang_behavior<type>;

    bool is_above() {
        return behavior::isAbove(value, high);
    }

    bool is_below() {
        return behavior::isBelow(value, low);
    }

    void set_state(int value) {
        state = value;
        digitalWrite(outport, state);
    }

    void turn_on() {
        set_state(HIGH);
    }

    void turn_off() {
        set_state(LOW);
    }

public:
    simple_bang_bang() {
        pinMode(outport, OUTPUT);
        pinMode(inport, INPUT);
    }

    void initialize(const char *name, int low, int high) {
        this->name = name;
        this->low = low;
        this->high = high;
        this->initialized = true;
    }

    void sense() override {
        value = analogRead(inport);
    }

    void actualize() override {
        ETL_ASSERT (initialized, "Uninitialized controller");
        if (is_below() && is_off()) {
            turn_on();
        } else if (is_above() && is_on()) {
            turn_off();
        }
    }

    bool ETL_CONSTEXPR17 is_heater() const {
        return type == HEATER;
    }

    bool ETL_CONSTEXPR17 is_cooler() const {
        return type == COOLER;
    }

    bool is_off() {
        return state == LOW;
    }

    bool is_on() {
        return state == HIGH;
    }

    void set_target_low(int target) {
        low = target;
    }

    void set_target_high(int target) {
        high = target;
    }

    int get_target_low(int target) const {
        return low;
    }

    int get_target_high(int target) const {
        return high;
    }
};

template<uint8_t inport, uint8_t outport>
using heater_bang_bang = simple_bang_bang<inport, outport, HEATER>;

template<uint8_t inport, uint8_t outport>
using cooler_bang_bang = simple_bang_bang<inport, outport, COOLER>;

#endif //HUMIDITY_H
