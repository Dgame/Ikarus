//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_INTEGEREXPRESSION_HPP
#define IKARUS_INTEGEREXPRESSION_HPP

#include "Expression.hpp"
#include <memory>
#include <NumericValue.hpp>

namespace ik {
    class AddExpression : public Expression {
    private:
        std::unique_ptr<const Value> _left;
        std::unique_ptr<const Value> _right;

    public:
        explicit AddExpression(const Value*, const Value*);

        const Value* getLeft() const {
            return _left.get();
        }

        const Value* getRight() const {
            return _right.get();
        }

        virtual void accept(ExpressionVisitor*) const;
    };
}

#endif //IKARUS_INTEGEREXPRESSION_HPP
