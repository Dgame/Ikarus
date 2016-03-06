//
// Created by Bjarne on 06.03.2016.
//

#include "ArrayValue.hpp"
#include "ImmutableValueVisitor.hpp"
#include "MutableValueVisitor.hpp"

ArrayValue::ArrayValue(u32_t amount) {
    amount = amount > 0 ? amount : 8;
    _values.reserve(amount);
}

void ArrayValue::assign(const Value* value) {
    if (_index >= _values.size()) {
        _values.resize(_index * 2);
    }

    _values.at(_index).reset(value);
    _index++;
}

void ArrayValue::accept(ImmutableValueVisitor* ivv) const {
    ivv->visit(this);
}

void ArrayValue::accept(MutableValueVisitor* mvv) {
    mvv->visit(this);
}
