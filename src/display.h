//
// Created by glenneric.hall on 07/05/2025.
//

#ifndef GREENHOUSE_DISPLAY_H
#define GREENHOUSE_DISPLAY_H

struct display {

    virtual void title(const char* title) = 0;

    virtual void value() = 0;
};

#endif //GREENHOUSE_DISPLAY_H
