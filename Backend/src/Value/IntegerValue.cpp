//
// Created by Randy on 06.03.2016.
//
#include "../../include/Value/IntegerValue.hpp"
#include "../../include/Visitor/ValueVisitor.hpp"

namespace ik {
    IntegerValue::IntegerValue(int value) : _value(value) { }

    IntegerValue* IntegerValue::clone() const {
        return new IntegerValue(_value);
    }

    void IntegerValue::accept(ValueVisitor* v) const {
        v->visit(this);
    }
}