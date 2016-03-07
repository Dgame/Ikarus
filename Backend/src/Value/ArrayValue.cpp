//
// Created by Bjarne on 06.03.2016.
//

#include "ArrayValue.hpp"
#include "ValueVisitor.hpp"
#include "ValueRevelation.hpp"
#include "compare.hpp"

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

Compare ArrayValue::compare(const Value* value) const {
    ImmutableValueRevelation ivr;
    value->accept(&ivr);

    if (ivr.array == nullptr) {
        return Compare::IS_NOT_EQUAL;
    }

    if (ivr.array->getAmount() > this->getAmount()) {
        return Compare::IS_LOWER;
    }

    if (ivr.array->getAmount() < this->getAmount()) {
        return Compare::IS_GREATER;
    }

    for (u32_t i = 0; i < this->getAmount(); i++) {
        if (this->fetch(i)->compare(ivr.array->fetch(i)) != Compare::IS_EQUAL) {
            return Compare::IS_NOT_EQUAL;
        }
    }

    return Compare::IS_EQUAL;
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