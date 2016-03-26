#ifndef IKARUS_VARIABLE_EXPRESSION_HPP
#define IKARUS_VARIABLE_EXPRESSION_HPP

#include <Declaration/VariableDeclaration.hpp>
#include "Expression.hpp"

class VariableExpression : public Expression {
private:
    VariableDeclaration* _var = nullptr;

public:
    explicit VariableExpression(VariableDeclaration* var) : _var(var) { }

    virtual VariableExpression* clone() const override {
        return new VariableExpression(_var);
    }

    VariableDeclaration* getVariableDeclaration() const {
        return _var;
    }

    virtual void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_VARIABLE_EXPRESSION_HPP
