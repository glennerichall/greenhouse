//
// Created by glenneric.hall on 08/05/2025.
//

#ifndef GREENHOUSE_LCD_16_2_CONFIGURATOR_H
#define GREENHOUSE_LCD_16_2_CONFIGURATOR_H

#include "display.h"

struct controller;

#include <etl/array.h>

struct lc2_16_2_configurator {
private:
    etl::array<uint8_t> buttons;
public:

    void sense();

    void config(display&, controller &);
};



#endif //GREENHOUSE_LCD_16_2_CONFIGURATOR_H
