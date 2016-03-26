#ifndef IKARUS_MOD_EXPRESSION_HPP
#define IKARUS_MOD_EXPRESSION_HPP

#include "BinaryExpression.hpp"

class ModuloExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    ModuloExpression* clone() const override {
        return new ModuloExpression(this->getLeftExpression()->clone(), this->getRightExpression()->clone());
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_MOD_EXPRESSION_HPP
