#ifndef IKARUS_REVELATIONVISITOR_HPP
#define IKARUS_REVELATIONVISITOR_HPP

#include "Visitor.hpp"

template <typename T, typename std::enable_if<std::is_base_of<Expression, T>::value, i32_t>::type = 0>
class RevelationVisitor : public Visitor {
private:
    T* _exp = nullptr;

public:
    virtual void visit(T* exp) {
        _exp = exp;
    }

    T* getExpression() {
        return _exp;
    }

    bool isValid() const {
        return _exp != nullptr;
    }
};

#endif //IKARUS_REVELATIONVISITOR_HPP
