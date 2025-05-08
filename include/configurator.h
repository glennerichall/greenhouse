//
// Created by glenneric.hall on 08/05/2025.
//

#ifndef GREENHOUSE_CONFIGURATOR_H
#define GREENHOUSE_CONFIGURATOR_H

struct display;
struct controller;

struct configurator {
public:
    virtual bool is_active() = 0;

    virtual void config(display&, controller&) = 0;
};

#endif //GREENHOUSE_CONFIGURATOR_H
