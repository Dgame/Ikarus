//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_MATHEXPRESSIONVISITOR_HPP
#define IKARUS_MATHEXPRESSIONVISITOR_HPP

#include "ExpressionVisitor.hpp"
#include <types.hpp>

namespace ik {
    class MathExpressionVisitor : public ExpressionVisitor {
    private:
        f32_t _value = 0;

    public:
        f32_t getValue() const {
            return _value;
        }

        virtual void visit(const AddExpression*);
    };
}

#endif //IKARUS_MATHEXPRESSIONVISITOR_HPP
