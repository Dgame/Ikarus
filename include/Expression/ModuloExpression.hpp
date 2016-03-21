#ifndef IKARUS_MODEXPRESSION_HPP
#define IKARUS_MODEXPRESSION_HPP

#include "BinaryExpression.hpp"

class ModuloExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    virtual ModuloExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_MODEXPRESSION_HPP
