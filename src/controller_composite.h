//
// Created by glenn on 05/05/25.
//

#ifndef CONTROLLER_COMPOSITE_H
#define CONTROLLER_COMPOSITE_H

#include <controller.h>
#include <traits.h>


// --- controller_composite (variadic template) ---

template<typename... controllers>
struct controller_composite;

// Recursive specialization
template<typename first, typename... rest>
struct controller_composite<first, rest...> {
    enum { unique_check = are_unique<first, rest...>::value };
    // Force compile-time error if types are not unique
    typedef char unique_check_failed[unique_check ? 1 : -1];

private:
    first _first;
    controller_composite<rest...> _rest;

public:
    controller_composite() {}

    void update() {
        _first.update();
        _rest.update();
    }

    // at<T> - match
    template<typename T>
    typename enable_if<is_same<T, first>::value, T&>::type
    at() {
        return _first;
    }

    // at<T> - recurse
    template<typename T>
    typename enable_if<!is_same<T, first>::value, T&>::type
    at() {
        return _rest.template at<T>();
    }
};

// Base case
template<>
struct controller_composite<> {
    void update() {}
};



#endif //CONTROLLER_COMPOSITE_H
