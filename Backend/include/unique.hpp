//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_UNIQUE_HPP
#define IKARUS_UNIQUE_HPP

#include <memory>

namespace std {
    template <typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif //IKARUS_UNIQUE_HPP
