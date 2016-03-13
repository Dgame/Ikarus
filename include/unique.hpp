#ifndef IKARUS_UNIQUE_HPP
#define IKARUS_UNIQUE_HPP

#include <memory>

namespace std {
    template <typename T, typename ...Args>
    auto make_unique(Args&& ...args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif //IKARUS_UNIQUE_HPP