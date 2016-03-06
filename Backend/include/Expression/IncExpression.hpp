//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_INCEXPRESSION_HPP
#define IKARUS_INCEXPRESSION_HPP

#include "UnaryExpression.hpp"

namespace ik {
    class IncExpression : public UnaryExpression {
    public:
        explicit IncExpression(const Value*);

        virtual void accept(ExpressionVisitor*) const;
    };
}

#endif //IKARUS_INCEXPRESSION_HPP
