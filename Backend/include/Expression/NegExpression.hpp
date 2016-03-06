//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_NEGEXPRESSION_HPP
#define IKARUS_NEGEXPRESSION_HPP

#include "UnaryExpression.hpp"

namespace ik {
    class NegExpression : public UnaryExpression {
    public:
        explicit NegExpression(const Value*);

        virtual void accept(ExpressionVisitor*) const;
    };
}

#endif //IKARUS_NEGEXPRESSION_HPP
