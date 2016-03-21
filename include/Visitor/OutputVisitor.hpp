#ifndef IKARUS_OUTPUTVISITOR_HPP
#define IKARUS_OUTPUTVISITOR_HPP

#include "Visitor.hpp"
#include <iostream>
#include <memory>

class OutputVisitor : public Visitor {
private:
    std::ostream& _out;

public:
    explicit OutputVisitor(std::ostream&);

    virtual void visit(StringExpression*) override;
    virtual void visit(NumericExpression*) override;
    virtual void visit(ArrayExpression*) override;
};

class Expression;

void print(Expression*, bool nl = true);

#endif //IKARUS_OUTPUTVISITOR_HPP
