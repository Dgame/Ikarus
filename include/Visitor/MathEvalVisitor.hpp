#ifndef IKARUS_MATHEVALVISITOR_HPP
#define IKARUS_MATHEVALVISITOR_HPP

#include <iostream>
#include <Expression/VariableExpression.hpp>
#include "Visitor.hpp"
#include "types.hpp"

class BinaryExpression;

class UnaryExpression;

class MathEvalVisitor : public Visitor {
private:
    std::ostream& _out;

    void binary(const std::string&, BinaryExpression*);

    void unary(const std::string&, UnaryExpression*);

public:
    explicit MathEvalVisitor(std::ostream&);

    void visit(NumericExpression*) override;

    void visit(NotExpression*) override;

    void visit(NegateExpression*) override;

    void visit(VariableExpression*) override;

    void visit(AddExpression*) override;

    void visit(SubtractExpression*) override;

    void visit(MultiplyExpression*) override;

    void visit(DivideExpression*) override;

    void visit(ModuloExpression*) override;

    void visit(IncrementExpression*) override;

    void visit(DecrementExpression*) override;

    void visit(IndexAssignExpression*) override;

    void visit(IndexAccessExpression*) override;
};

#endif //IKARUS_MATHEVALVISITOR_HPP
