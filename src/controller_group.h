//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_CONTROLLER_GROUP_H
#define GREENHOUSE_CONTROLLER_GROUP_H

#include <controller.h>

struct controller_group {
private:

    controller* controllers{nullptr};

public:

    void add(controller* controller);
};

#endif //GREENHOUSE_CONTROLLER_GROUP_H
