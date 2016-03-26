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

class StringExpression;
class NumericExpression;
class ArrayExpression;
class VarExpression;
class OffsetExpression;

class BoolExpression;
class CastExpression;
class IndexAccessExpression;
class IndexAssignExpression;
class LowerExpression;
class GreaterExpression;
class LowerEqualExpression;
class GreaterEqualExpression;
class EqualExpression;
class NotEqualExpression;

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

    virtual void visit(StringExpression*) { }
    virtual void visit(NumericExpression*) { }
    virtual void visit(ArrayExpression*) { }
    virtual void visit(VarExpression*) { }
    virtual void visit(OffsetExpression*) { }

    virtual void visit(BoolExpression*) { }
    virtual void visit(CastExpression*) { }
    virtual void visit(IndexAccessExpression*) { }
    virtual void visit(IndexAssignExpression*) { }
    virtual void visit(LowerExpression*) { }
    virtual void visit(GreaterExpression*) { }
    virtual void visit(LowerEqualExpression*) { }
    virtual void visit(GreaterEqualExpression*) { }
    virtual void visit(EqualExpression*) { }
    virtual void visit(NotEqualExpression*) { }

    virtual void visit(VariableDeclaration*) { }
    virtual void visit(OffsetDeclaration*) { }
    virtual void visit(ValueDeclaration*) { }
};

#endif //IKARUS_VISITOR_HPP
