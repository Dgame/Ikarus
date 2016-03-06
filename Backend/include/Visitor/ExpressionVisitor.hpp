//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_EXPRESSION_VISITOR_HPP
#define IKARUS_EXPRESSION_VISITOR_HPP

namespace ik {
    class AddExpression;
    class SubExpression;
    class MulExpression;
    class DivExpression;
    class ModExpression;
    class NotExpression;
    class NegExpression;
    class IncExpression;
    class DecExpression;

    class ExpressionVisitor {
    public:
        virtual void visit(const AddExpression*) = 0;
        virtual void visit(const SubExpression*) = 0;
        virtual void visit(const MulExpression*) = 0;
        virtual void visit(const DivExpression*) = 0;
        virtual void visit(const ModExpression*) = 0;
        virtual void visit(const NotExpression*) = 0;
        virtual void visit(const NegExpression*) = 0;
        virtual void visit(const IncExpression*) = 0;
        virtual void visit(const DecExpression*) = 0;
    };
}

#endif //IKARUS_VISITOR_HPP
