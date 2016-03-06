//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_UNARYEXPRESSION_HPP
#define IKARUS_UNARYEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>
#include "Value.hpp"

class UnaryExpression : public Expression {
private:
    std::unique_ptr<const Value> _value;

public:
    explicit UnaryExpression(const Value*);

    const Value* getValue() const {
        return _value.get();
    }
};

#endif //IKARUS_UNARYEXPRESSION_HPP
