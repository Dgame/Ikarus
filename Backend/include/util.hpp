//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_UTIL_HPP
#define IKARUS_UTIL_HPP

#include <iostream>

template <typename T>
void writeln(const T& val) {
    std::cout << val << std::endl;
}

template <typename T, typename ...Args>
void writeln(const T& val, const Args ...args) {
    std::cout << val;
    writeln(args...);
}

template <typename T, typename ...Args>
void debug(const T& val, const Args ...args) {
#if DEBUG
    writeln(val, args...);
#endif
};

template <typename ...Args>
void error(const Args ...args) {
    writeln(args...);

    throw "An error occured";
}

template <typename ...Args>
void enforce(bool cond, const Args ...args) {
    if (!cond) {
        error(args...);
    }
}

#endif //IKARUS_UTIL_HPP
