#ifndef IKARUS_UNARY_EXPRESSION_HPP
#define IKARUS_UNARY_EXPRESSION_HPP

#include "Expression.hpp"
#include <memory>

class UnaryExpression : public Expression {
private:
    std::unique_ptr<Expression> _expr;

public:
    explicit UnaryExpression(Expression*);

    Expression* getExpression() {
        return _expr.get();
    }

    const Expression* getExpression() const {
        return _expr.get();
    }

    bool isAtomic() const override {
        return false;
    }
};

#endif //IKARUS_UNARY_EXPRESSION_HPP
