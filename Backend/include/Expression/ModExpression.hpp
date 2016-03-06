//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_MODEXPRESSION_HPP
#define IKARUS_MODEXPRESSION_HPP

#include "BinaryExpression.hpp"

namespace ik {
    class ModExpression : public BinaryExpression {
    public:
        explicit ModExpression(const Value*, const Value*);

        virtual void accept(ExpressionVisitor*) const;
    };
}

#endif //IKARUS_MODEXPRESSION_HPP
