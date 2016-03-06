//
// Created by Randy on 06.03.2016.
//
#include <NumericValue.hpp>
#include <ValueVisitor.hpp>

namespace ik {
    NumericValue::NumericValue(f32_t value) : _value(value) { }

    NumericValue* NumericValue::clone() const {
        return new NumericValue(_value);
    }

    void NumericValue::accept(ValueVisitor* v) const {
        v->visit(this);
    }
}