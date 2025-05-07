//
// Created by glenneric.hall on 07/05/2025.
//

#include "controller_group.h"

void controller_group::add(controller* controller) {
    controllers.push_back(controller);
}

void controller_group::add(controller &&controller) {

}
