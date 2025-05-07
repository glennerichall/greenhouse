//
// Created by glenn on 05/05/25.
//

#ifndef CONTROLLER_COMPOSITE_H
#define CONTROLLER_COMPOSITE_H

#include "controller.h"
#include "traits.h"
#include <etl/platform.h>


template<typename... controllers>
struct controller_composite;

// Recursive specialization
template<typename first, typename... rest>
struct controller_composite<first, rest...> : controller {

private:
    first _first;
    controller_composite<rest...> _rest;

public:
    controller_composite() = default;

    void update() override {
        _first.update();
        _rest.update();
    }

    void sense() override {
        _first.sense();
        _rest.sense();
    }

    void actualize() override {
        _first.actualize();
        _rest.actualize();
    }


    // at<T> - match
    template<typename T>
    typename enable_if<is_same<T, first>::value, T &>::type
    at() {
        return _first;
    }

    // at<T> - recurse
    template<typename T>
    typename enable_if<!is_same<T, first>::value, T &>::type
    at() {
        return _rest.template at<T>();
    }

    template<typename T>
    T &at(size_t index) const {
        if ETL_CONSTEXPR17 (index == 0) {
            return _first;
        } else {
            return _rest.at(index - 1);
        }
    }
};

// Base case
template<>
struct controller_composite<> {
    void update() {}

    void sense() {}

    void actualize() {}
};


#endif //CONTROLLER_COMPOSITE_H
