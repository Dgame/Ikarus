#ifndef IKARUS_MATHVISITOR_HPP
#define IKARUS_MATHVISITOR_HPP

#include "Visitor.hpp"
#include "types.hpp"

class MathVisitor : public Visitor {
private:
    f32_t _value = 0;

public:
    f32_t getValue() const {
        return _value;
    }

    void visit(NumericExpression*) override;

    void visit(NotExpression*) override;
    void visit(NegateExpression*) override;

    void visit(AddExpression*) override;
    void visit(SubtractExpression*) override;
    void visit(MultiplyExpression*) override;
    void visit(DivideExpression*) override;
    void visit(ModuloExpression*) override;
    void visit(IncrementExpression*) override;
    void visit(DecrementExpression*) override;
};

#endif //IKARUS_MATHVISITOR_HPP