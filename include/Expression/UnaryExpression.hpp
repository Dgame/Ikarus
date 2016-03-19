#ifndef IKARUS_UNARYEXPRESSION_HPP
#define IKARUS_UNARYEXPRESSION_HPP

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

    virtual bool isAtomic() const {
        return false;
    }
};

#endif //IKARUS_UNARYEXPRESSION_HPP
