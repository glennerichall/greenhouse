//
// Created by glenneric.hall on 08/05/2025.
//

#include "greenhouse.h"

void greenhouse::update() {
    if (_configurator.is_active()) {
        _configurator.config(_display, _controllers);
    } else {
        _controllers.update();
    }
    delay(1000);
}


void greenhouse::initialize() {
    _controllers.at<humidity>().initialize(
            "Humidity", 50, 100);

    _controllers.at<light>().initialize(
            "Lighting", 50, 100);

    _display.initialize();
}
