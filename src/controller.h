//
// Created by glenn on 05/05/25.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "display.h"

struct controller {
        controller() = default;

        virtual void sense() = 0;

        virtual void actualize()  = 0;

        virtual void print(display&) = 0;

        virtual void update();

        virtual ~controller() = default;
    };


#endif //CONTROLLER_H
