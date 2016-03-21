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

    virtual void visit(NumericExpression*) override;

    virtual void visit(NotExpression*) override;
    virtual void visit(NegateExpression*) override;

    virtual void visit(AddExpression*) override;
    virtual void visit(SubtractExpression*) override;
    virtual void visit(MultiplyExpression*) override;
    virtual void visit(DivideExpression*) override;
    virtual void visit(ModuloExpression*) override;
    virtual void visit(IncrementExpression*) override;
    virtual void visit(DecrementExpression*) override;
};

#endif //IKARUS_MATHVISITOR_HPP