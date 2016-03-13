#ifndef IKARUS_EXPRESSION_HPP
#define IKARUS_EXPRESSION_HPP

#include "Visitable.hpp"

class NumericExpression;

class Expression : public Visitable {
public:
    virtual ~Expression() { }

    virtual Expression* clone() const = 0;

    virtual const NumericExpression* isNumeric() const {
        return nullptr;
    }
};

#endif //IKARUS_EXPRESSION_HPP
