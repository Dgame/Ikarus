#ifndef IKARUS_STRINGEXPRESSION_HPP
#define IKARUS_STRINGEXPRESSION_HPP

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

    virtual StringExpression* clone() const override{
        return new StringExpression(_value);
    }

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_STRINGEXPRESSION_HPP
