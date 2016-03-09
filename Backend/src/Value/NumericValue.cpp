//
// Created by Randy on 06.03.2016.
//
#include "NumericValue.hpp"
#include "NumericValueVisitor.hpp"
#include "compare.hpp"

#include <limits>

NumericValue::NumericValue(f32_t value) : _value(value) { }

NumericValue* NumericValue::clone() const {
    return new NumericValue(_value);
}

Compare NumericValue::compare(const Value* value) const {
    if (value == nullptr) {
        return Compare::IS_NOT_EQUAL;
    }

    NumericValueVisitor nvv;
    value->accept(nvv);

    if (std::fabs(_value - nvv.getNumber()) < std::numeric_limits<f32_t>::epsilon()) {
        return Compare::IS_EQUAL;
    }

    if (_value > nvv.getNumber()) {
        return Compare::IS_GREATER;
    }

    debug(_value, " vs ", nvv.getNumber());

    return Compare::IS_LOWER;
}

void NumericValue::accept(ImmutableValueVisitor& ivv) const {
    ivv.visit(this);
}

void NumericValue::accept(MutableValueVisitor& mvv) {
    mvv.visit(this);
}
