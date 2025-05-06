//
// Created by glenn on 05/05/25.
//

#ifndef GREENHOUSE_H
#define GREENHOUSE_H

#include <controller.h>


template<typename... controllers>
struct greenhouse;

template<typename first, typename... rest>
struct greenhouse<first, rest...> {

private:
    first _first;
    greenhouse<rest...> _rest;

public:
    greenhouse() = default;

    void update() {
        _first.update();
        _rest.update();
    }
};

template<>
struct greenhouse<> {
    void update() {
    }
};

#endif //GREENHOUSE_H
