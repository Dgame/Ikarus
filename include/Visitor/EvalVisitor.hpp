#ifndef IKARUS_EVALVISITOR_HPP
#define IKARUS_EVALVISITOR_HPP

#include <iostream>
#include <Expression/VariableExpression.hpp>
#include "types.hpp"
#include "Visitor.hpp"

class VariableDeclaration;
class BinaryExpression;

class EvalVisitor : public Visitor {
private:
    enum State {
        NONE = 0,
        VARIABLE = 1,
        MATH = 2
    };

    size_t _vid = 0;
    u32_t _state = NONE;
    u32_t _stack_offset = 0;

    std::ostream& _out;

    virtual void math(const std::string&, BinaryExpression*);

public:
    explicit EvalVisitor(std::ostream&);

    void visit(MultiplyExpression*) override;
    void visit(AddExpression*) override;

    void visit(VariableExpression*) override;
    void visit(IndexAssignExpression*) override;

    void visit(NumericExpression*) override;
    void visit(ArrayExpression*) override;
    void visit(VariableDeclaration*) override;
};

#endif //IKARUS_EVALVISITOR_HPP
