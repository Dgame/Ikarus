#ifndef IKARUS_EXPRESSION_HPP
#define IKARUS_EXPRESSION_HPP

#include "Visitable.hpp"

class NumericExpression;

class Expression : public Visitable {
public:
    virtual ~Expression() { }

    virtual Expression* clone() const = 0;
};

#endif //IKARUS_EXPRESSION_HPP
