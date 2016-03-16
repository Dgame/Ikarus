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

    virtual void visit(NumericExpression*);

    virtual void visit(NotExpression*);
    virtual void visit(NegateExpression*);

    virtual void visit(AddExpression*);
    virtual void visit(SubtractExpression*);
    virtual void visit(MultiplyExpression*);
    virtual void visit(DivideExpression*);
    virtual void visit(ModuloExpression*);
    virtual void visit(IncrementExpression*);
    virtual void visit(DecrementExpression*);
};

#endif //IKARUS_MATHVISITOR_HPP