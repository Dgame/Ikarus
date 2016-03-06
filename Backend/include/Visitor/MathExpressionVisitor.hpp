//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_MATHEXPRESSIONVISITOR_HPP
#define IKARUS_MATHEXPRESSIONVISITOR_HPP

#include "ExpressionVisitor.hpp"

namespace ik {
    class MathExpressionVisitor : public ExpressionVisitor {
    private:
        int _value = 0;

    public:
        int getValue() const {
            return _value;
        }

        virtual void visit(const AddExpression*);
    };
}

#endif //IKARUS_MATHEXPRESSIONVISITOR_HPP
