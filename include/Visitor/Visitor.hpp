#ifndef IKARUS_VISITOR_HPP
#define IKARUS_VISITOR_HPP

class AddExpression;
class DecrementExpression;
class DivideExpression;
class IncrementExpression;
class ModuloExpression;
class MultiplyExpression;
class NegateExpression;
class NotExpression;
class SubtractExpression;

class NumericExpression;
class ArrayExpression;
class VarExpression;
class OffsetExpression;

class VariableDeclaration;
class OffsetDeclaration;
class ValueDeclaration;

class Visitor {
public:
    virtual void visit(AddExpression*) { }
    virtual void visit(DecrementExpression*) { }
    virtual void visit(DivideExpression*) { }
    virtual void visit(IncrementExpression*) { }
    virtual void visit(ModuloExpression*) { }
    virtual void visit(MultiplyExpression*) { }
    virtual void visit(NegateExpression*) { }
    virtual void visit(NotExpression*) { }
    virtual void visit(SubtractExpression*) { }

    virtual void visit(NumericExpression*) { }
    virtual void visit(ArrayExpression*) { }
    virtual void visit(VarExpression*) { }
    virtual void visit(OffsetExpression*) { }

    virtual void visit(VariableDeclaration*) { }
    virtual void visit(OffsetDeclaration*) { }
    virtual void visit(ValueDeclaration*) { }
};

#endif //IKARUS_VISITOR_HPP