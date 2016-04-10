#ifndef IKARUS_EVAL_VISITOR_HPP
#define IKARUS_EVAL_VISITOR_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <Expression/Expression.hpp>
#include <Expression/NotExpression.hpp>
#include <Expression/NegateExpression.hpp>
#include "types.hpp"
#include "Visitor.hpp"
#include "Backend/VM/Operand.hpp"

class BinaryExpression;

class UnaryExpression;

class EvalVisitor : public Visitor {
private:
    std::vector<std::unique_ptr<Backend::Operand>> _operands;
    std::ostream& _out;

    void eval(Expression*);

public:
    explicit EvalVisitor(std::ostream&);

    auto& getOperands() const {
        return _operands;
    }

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

    void visit(NotExpression*) override;

    void visit(NegateExpression*) override;
};

#endif //IKARUS_EVAL_VISITOR_HPP
