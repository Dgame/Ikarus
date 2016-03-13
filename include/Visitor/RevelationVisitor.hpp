#ifndef IKARUS_REVELATIONVISITOR_HPP
#define IKARUS_REVELATIONVISITOR_HPP

#include "Visitor.hpp"

class RevelationVisitor : public Visitor {
public:
    NumericExpression* numeric = nullptr;
    ArrayExpression* array = nullptr;

    void reset() {
        this->numeric = nullptr;
        this->array = nullptr;
    }

    virtual void visit(NumericExpression* exp) {
        this->numeric = exp;
    }

    virtual void visit(ArrayExpression* exp) {
        this->array = exp;
    }
};

#endif //IKARUS_REVELATIONVISITOR_HPP
