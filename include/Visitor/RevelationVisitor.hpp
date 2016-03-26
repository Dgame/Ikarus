#ifndef IKARUS_REVELATIONVISITOR_HPP
#define IKARUS_REVELATIONVISITOR_HPP

#include "Visitor.hpp"

template <typename T>
class RevelationVisitor : public Visitor {
private:
    T* _exp = nullptr;

public:
    void visit(T* exp) override {
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
