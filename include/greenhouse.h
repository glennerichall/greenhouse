//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_GREENHOUSE_H
#define GREENHOUSE_GREENHOUSE_H

#include <simple_bang_bang.h>
#include <controller_composite.h>
#include <defs.h>
#include "lcd_display.h"
#include "lcd_16_2_configurator.h"

using humidity = heater_bang_bang<A0, D6>;
using light = heater_bang_bang<A1, D7>;
using lcd = lcd_16_2<D12, D11, D5, D4, D3, D2>;

struct greenhouse {
private:
    lcd _display;
    controller_composite<humidity, light> _controllers;
    lcd_16_2_configurator _configurator;

public:
    greenhouse() = default;

    void update();

    void initialize();

    ~greenhouse() = default;
};



#endif //GREENHOUSE_GREENHOUSE_H
