//
// Created by glenn on 05/05/25.
//

#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <controller.h>

template<bool heatUp>
struct bang_bang_behavior;

// Specialization for heatUp = true (heating device)
template<>
struct bang_bang_behavior<true> {
    static bool isBelow(int value, int low)   { return value < low; }
    static bool isAbove(int value, int high)   { return value > high; }
};

// Specialization for heatUp = false (cooling device)
template<>
struct bang_bang_behavior<false> {
    static bool isBelow(int value, int low)   { return value > low; /* ie -value < -low */}
    static bool isAbove(int value, int high)   { return value < high; }
};

template<
    uint8_t inport,
    uint8_t outport,
    bool heatUp
>
struct simple_bang_bang : controller {
private:
    enum STATE {
        ON = HIGH,
        OFF = LOW,
    };

    int value{};
    int state{LOW};
    int high{0}, low{0};

    using behavior = bang_bang_behavior<heatUp>;

    bool isOff() {
        return state == LOW;
    }

    bool isOn() {
        return state == HIGH;
    }

    bool isAbove() {
        return behavior::isAbove(value);
    }

    bool isBelow() {
        return behavior::isBelow(value);
    }

    void setState(int value) {
        state = value;
        digitalWrite(outport, state);
    }

    void turnOn() {
        setState(ON);
    }

    void turnOff() {
        setState(OFF);
    }

public:
    simple_bang_bang() {
        pinMode(outport, OUTPUT);
        pinMode(inport, INPUT);
    }

    void sense() override {
        value = analogRead(inport);
    }

    void actualize() override {
        if (isBelow() && isOff()) {
            turnOn();
        } else if (isAbove() && isOn()) {
            turnOff();
        }
    }

    void display() override {

    }
};


#endif //HUMIDITY_H
