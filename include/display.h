//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_DISPLAY_H
#define GREENHOUSE_DISPLAY_H

struct controller;

struct display {
public:
    virtual void print_state(const controller &ctrl) = 0;

    virtual void initialize() = 0;

    virtual ~display() = default;
};

#endif //GREENHOUSE_DISPLAY_H
