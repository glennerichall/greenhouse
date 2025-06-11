//
// Created by glenn on 18/05/25.
//

#include "timer.h"

#include <Arduino.h>

timer::pending::pending(::timer_callback cb, unsigned long to): callback(cb), timeout(to) {
}

void timer::on_timeout() {
}

void timer::init() {
    if (_initialized) return;
    _initialized = true;
}

bool timer::loop() {
    auto now = millis();
    _delta = now - _last;

    decltype(_tasks) cpy;

    for (size_t i = 0; i < _tasks.size(); ++i) {
        auto &task = _tasks[i];
        if (now > task.timeout) {
            task.callback();
        } else {
            cpy.push_back(static_cast<pending &&>(task));
        }
    }
    _last = now;
    etl::swap(cpy, _tasks);
    return _tasks.size() > 0;
}

void timer::set_timeout_sync(timer_callback cb, unsigned long timeout) {
    auto now = millis();
    _tasks.emplace_back(cb, now + timeout);
}


bool timer::_initialized{false};
unsigned long timer::_last{0};
unsigned long timer::_delta{0};
etl::vector<timer::pending, 20> timer::_tasks;
