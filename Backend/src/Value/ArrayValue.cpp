//
// Created by Bjarne on 06.03.2016.
//

#include "ArrayValue.hpp"
#include "ImmutableValueVisitor.hpp"
#include "MutableValueVisitor.hpp"

ArrayValue::ArrayValue(u32_t amount) : _values(amount) { }

void ArrayValue::assign(const Value* value) {
    if (_index >= _values.size()) {
        _values.resize(_index * 2);
    }

    _values.at(_index).reset(value);
    _index++;
}

ArrayValue* ArrayValue::clone() const {
    ArrayValue* av = new ArrayValue(this->getAmount());
    for (auto & value : _values) {
        av->assign(value->clone());
    }

    return av;
}

void ArrayValue::accept(ImmutableValueVisitor* ivv) const {
    ivv->visit(this);
}

void ArrayValue::accept(MutableValueVisitor* mvv) {
    mvv->visit(this);
}

std::ostream& ArrayValue::output(std::ostream& out) const {
    out << '[';
    for (auto& value : _values) {
        value->output(out);
    }
    out << ']';

    return out;
}