//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_CONTROLLER_GROUP_H
#define GREENHOUSE_CONTROLLER_GROUP_H

#include "controller.h"
#include <etl/vector.h>

#define MAX_CONTROLLERS 100

using vector = etl::vector<controller*, MAX_CONTROLLERS>;

struct controller_group : controller {
private:

    vector controllers;

public:

    void add(controller* controller);

    void add(controller&& controller);
};

#endif //GREENHOUSE_CONTROLLER_GROUP_H
