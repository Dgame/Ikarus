//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_ASSIGNVALUEVISITOR_HPP
#define IKARUS_ASSIGNVALUEVISITOR_HPP

#include "MutableValueVisitor.hpp"

class Value;

class AssignValueVisitor : public MutableValueVisitor {
private:
    ArrayValue* _array = nullptr;
    const Value* _item = nullptr;

public:
    explicit AssignValueVisitor(Value*, const Value*);

    ArrayValue* getArrayValue() {
        return _array;
    }

    virtual void visit(NumericValue*);

    virtual void visit(ArrayValue*);
};

#endif //IKARUS_ASSIGNVALUEVISITOR_HPP
