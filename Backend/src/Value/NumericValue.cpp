//
// Created by Randy on 06.03.2016.
//
#include "NumericValue.hpp"
#include "ImmutableValueVisitor.hpp"
#include "MutableValueVisitor.hpp"

NumericValue::NumericValue(f32_t value) : _value(value) { }

NumericValue* NumericValue::clone() const {
    return new NumericValue(_value);
}

void NumericValue::accept(ImmutableValueVisitor* ivv) const {
    ivv->visit(this);
}

void NumericValue::accept(MutableValueVisitor* mvv) {
    mvv->visit(this);
}
