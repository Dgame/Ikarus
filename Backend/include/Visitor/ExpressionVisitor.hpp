//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_EXPRESSION_VISITOR_HPP
#define IKARUS_EXPRESSION_VISITOR_HPP

namespace ik {
    class AddExpression;

    class ExpressionVisitor {
    public:
        virtual void visit(const AddExpression*) = 0;
    };
}

#endif //IKARUS_VISITOR_HPP
