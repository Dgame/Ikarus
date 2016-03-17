#ifndef IKARUS_EXPRESSION_HPP
#define IKARUS_EXPRESSION_HPP

#include "Visitable.hpp"
#include "NullExpression.hpp"
#include "RevelationVisitor.hpp"

class Expression : public Visitable {
public:
    virtual ~Expression() { }

    template <typename T>
    NullExpression<T> is();

    virtual Expression* clone() const = 0;
};

template <typename T>
NullExpression<T> Expression::is() {
    RevelationVisitor<T> rv;
    this->accept(rv);

    return NullExpression<T>(rv.getExpression());
}

#endif //IKARUS_EXPRESSION_HPP
