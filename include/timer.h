//
// Created by glenn on 18/05/25.
//

#ifndef TIMER_H
#define TIMER_H

#include <etl/vector.h>

#include "ISR_Timer.hpp"

struct timer {
private:
    struct pending {
        timer_callback callback;
        unsigned long timeout;

        pending(timer_callback, unsigned long);
    };

    static bool _initialized;
    static unsigned long _last;
    static unsigned long _delta;
    static etl::vector<pending, 20> _tasks;

    static void on_timeout();

public:
    typedef void (*timer_callback)();

    static void init();

    static bool loop();

    static void set_timeout_sync(timer_callback cb, unsigned long timeout);

    static void remove_timeout_sync(timer_callback cb, unsigned long timeout);
};


#endif //TIMER_H
