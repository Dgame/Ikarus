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
        virtual void visit(const SubExpression*);
        virtual void visit(const MulExpression*);
        virtual void visit(const DivExpression*);
        virtual void visit(const ModExpression*);
        virtual void visit(const NotExpression*);
        virtual void visit(const NegExpression*);
        virtual void visit(const IncExpression*);
        virtual void visit(const DecExpression*);
    };
}

#endif //IKARUS_MATHEXPRESSIONVISITOR_HPP
