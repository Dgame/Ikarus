#ifndef IKARUS_BINARYEXPRESSION_HPP
#define IKARUS_BINARYEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>

class BinaryExpression : public Expression {
private:
    std::unique_ptr<Expression> _left;
    std::unique_ptr<Expression> _right;

public:
    explicit BinaryExpression(Expression*, Expression*);

    Expression* getLeftExpression() {
        return _left.get();
    }

    Expression* getRightExpression() {
        return _right.get();
    }

    const Expression* getLeftExpression() const {
        return _left.get();
    }

    const Expression* getRightExpression() const {
        return _right.get();
    }

    virtual bool isAtomic() const override {
        return false;
    }
};

#endif //IKARUS_BINARYEXPRESSION_HPP
