#ifndef IKARUS_BOOL_EXPRESSION_HPP
#define IKARUS_BOOL_EXPRESSION_HPP

#include "Expression.hpp"

class BoolExpression : public Expression {
private:
    bool _value = false;

public:
    explicit BoolExpression(bool value) : _value(value) { }

    bool getValue() const {
        return _value;
    }

    BoolExpression* clone() const {
        return new BoolExpression(_value);
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_BOOL_EXPRESSION_HPP
