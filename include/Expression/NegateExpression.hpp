#ifndef IKARUS_NEGEXPRESSION_HPP
#define IKARUS_NEGEXPRESSION_HPP

#include "UnaryExpression.hpp"

class NegateExpression : public UnaryExpression {
public:
    using UnaryExpression::UnaryExpression;

    virtual NegateExpression* clone() const override;

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_NEGEXPRESSION_HPP
