#ifndef IKARUS_VARIABLE_EXPRESSION_HPP
#define IKARUS_VARIABLE_EXPRESSION_HPP

#include "VariableDeclaration.hpp"
#include "Expression.hpp"

class VariableExpression : public Expression {
private:
    size_t _vid = 0;

protected:
    explicit VariableExpression(size_t vid) : _vid(vid) { }

public:
    explicit VariableExpression(VariableDeclaration* var) : VariableExpression(var->getId()) { }

    virtual VariableExpression* clone() const override {
        return new VariableExpression(_vid);
    }

    size_t getVariableId() const {
        return _vid;
    }

    virtual void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_VARIABLE_EXPRESSION_HPP
