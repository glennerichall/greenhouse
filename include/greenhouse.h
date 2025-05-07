//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_GREENHOUSE_H
#define GREENHOUSE_GREENHOUSE_H

#include <simple_bang_bang.h>
#include <controller_composite.h>
#include <defs.h>
#include "lcd_display.h"

using humidity = heater_bang_bang<A0, D6>;
using light = heater_bang_bang<A1, D7>;
using lcd = lcd_16_2<D12, D11, D5, D4, D3, D2>;

struct greenhouse {
private:
    lcd _display;

    controller_composite<humidity, light> _controllers;

public:
    greenhouse() = default;

    void update();

    void initialize();

    ~greenhouse() = default;
};


void greenhouse::update() {
    _controllers.update();
    _display.print_state(_controllers);
    delay(1000);
}


void greenhouse::initialize() {
    _controllers.at<humidity>().initialize(
            "Humidity", 50, 100);

    _controllers.at<light>().initialize(
            "Lighting", 50, 100);
}
#endif //GREENHOUSE_GREENHOUSE_H
