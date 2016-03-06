//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_NOTEXPRESSION_HPP
#define IKARUS_NOTEXPRESSION_HPP

#include "UnaryExpression.hpp"

namespace ik {
    class NotExpression : public UnaryExpression {
    public:
        explicit NotExpression(const Value*);

        virtual void accept(ExpressionVisitor*) const;
    };
}

#endif //IKARUS_NOTEXPRESSION_HPP
