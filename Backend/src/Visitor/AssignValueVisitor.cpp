//
// Created by Bjarne on 06.03.2016.
//

#include "AssignValueVisitor.hpp"
#include "NumericValue.hpp"
#include "ArrayValue.hpp"

AssignValueVisitor::AssignValueVisitor(Value* value, const Value* item) : _item(item) {
    value->accept(this);
}

void AssignValueVisitor::visit(NumericValue* value) {
    _array = new ArrayValue();
    _array->assign(value->clone());

    _array->accept(this);
}

void AssignValueVisitor::visit(ArrayValue* value) {
    value->assign(_item->clone());
}