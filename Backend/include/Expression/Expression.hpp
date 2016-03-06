//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_EXPRESSION_HPP
#define IKARUS_EXPRESSION_HPP

class ExpressionVisitor;

class Expression {
public:
    virtual void accept(ExpressionVisitor*) const = 0;
};

#endif //IKARUS_EXPRESSION_HPP
