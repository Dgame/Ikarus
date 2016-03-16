#ifndef IKARUS_APPENDVISITOR_HPP
#define IKARUS_APPENDVISITOR_HPP

#include "Visitor.hpp"

class ArrayExpression;

class AppendVisitor : public Visitor {
private:
    ArrayExpression* _array = nullptr;

public:
    ArrayExpression* getArrayExpression() {
        return _array;
    }

    virtual void visit(NumericExpression*);
    virtual void visit(ArrayExpression*);
};

#endif //IKARUS_APPENDVISITOR_HPP
