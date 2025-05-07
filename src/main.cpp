#include <Arduino.h>
#include "greenhouse.h"

greenhouse *gh;

void setup() {
    Serial.begin(115200, SERIAL_8N1);
    gh = new greenhouse();
    gh->initialize();
}

void loop() {
    gh->update();
}
