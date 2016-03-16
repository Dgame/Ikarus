#ifndef IKARUS_MODEXPRESSION_HPP
#define IKARUS_MODEXPRESSION_HPP

#include "BinaryExpression.hpp"

class ModuloExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual ModuloExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_MODEXPRESSION_HPP
