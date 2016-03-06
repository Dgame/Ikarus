//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_BINARYEXPRESSION_HPP
#define IKARUS_BINARYEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>
#include "Value.hpp"

namespace ik {
    class BinaryExpression : public Expression {
    private:
        std::unique_ptr<const Value> _left;
        std::unique_ptr<const Value> _right;

    public:
        explicit BinaryExpression(const Value*, const Value*);

        const Value* getLeft() const {
            return _left.get();
        }

        const Value* getRight() const {
            return _right.get();
        }
    };
}

#endif //IKARUS_BINARYEXPRESSION_HPP
