#ifndef IKARUS_EVALVISITOR_HPP
#define IKARUS_EVALVISITOR_HPP

#include <iostream>
#include "types.hpp"
#include "Visitor.hpp"
#include "Backend/VM/Code.hpp"

class VariableDeclaration;
class BinaryExpression;
class UnaryExpression;
class WhileStatement;

class EvalVisitor : public Visitor {
private:
    enum State {
        NONE = 0,
        VARIABLE = 1,
    };

    size_t _vid = 0;
    u32_t _state = NONE;
    u32_t _stack_offset = 0;

    Backend::Code _code;

    std::ostream& _out;

    virtual void math(const std::string&, BinaryExpression*);

    virtual void math(const std::string&, UnaryExpression*);

public:
    explicit EvalVisitor(std::ostream&);

    void visit(MultiplyExpression*) override;

    void visit(DivideExpression*) override;

    void visit(ModuloExpression*) override;

    void visit(AddExpression*) override;

    void visit(SubtractExpression*) override;

    void visit(IncrementExpression*) override;

    void visit(DecrementExpression*) override;

    void visit(VariableExpression*) override;

    void visit(IndexAssignExpression*) override;

    void visit(IndexAccessExpression*) override;

    void visit(LowerExpression*) override;

    void visit(GreaterExpression*) override;

    void visit(LowerEqualExpression*) override;

    void visit(GreaterEqualExpression*) override;

    void visit(EqualExpression*) override;

    void visit(NotEqualExpression*) override;

    void visit(NumericExpression*) override;

    void visit(ArrayExpression*) override;

    void visit(VariableDeclaration*) override;

    void visit(WhileStatement*) override;
};

#endif //IKARUS_EVALVISITOR_HPP
