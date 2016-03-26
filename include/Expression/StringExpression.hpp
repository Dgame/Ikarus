#ifndef IKARUS_STRING_EXPRESSION_HPP
#define IKARUS_STRING_EXPRESSION_HPP

#include <string>
#include "Expression.hpp"

class StringExpression : public Expression {
private:
    std::string _value;

public:
    explicit StringExpression(const std::string&);

    const std::string& getValue() const {
        return _value;
    }

    StringExpression* clone() const override {
        return new StringExpression(_value);
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_STRING_EXPRESSION_HPP
