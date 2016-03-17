#ifndef IKARUS_NULLOBJECT_HPP
#define IKARUS_NULLOBJECT_HPP

#include <string>
#include "util.hpp"
#include "types.hpp"

template <typename T>
class NullExpression {
private:
    T* _exp = nullptr;

public:
    explicit NullExpression(T* exp) : _exp(exp) { }

    T* ensure(const std::string& msg = "") {
        enforce(_exp != nullptr, "Unexpected type: ", msg);

        return _exp;
    }

    T* getExpression() {
        return _exp;
    }
};

#endif //IKARUS_NULLOBJECT_HPP
