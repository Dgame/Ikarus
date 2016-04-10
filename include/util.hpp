#ifndef IKARUS_UTIL_HPP
#define IKARUS_UTIL_HPP

#include <iostream>

#define DEBUG false

template <typename T>
void writeln(const T& val) {
    std::cout << val << '\n';
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

template <typename T, typename ...Args>
void error(const T& val, const Args ...args) {
    writeln(val, args...);

    throw "An error occured";
}

template <typename T, typename ...Args>
void enforce(bool cond, const T& val, const Args ...args) {
    if (!cond) {
        error(val, args...);
    }
}

template <typename T>
bool is(T* ptr) {
    return ptr != nullptr;
}

#endif //IKARUS_UTIL_HPP