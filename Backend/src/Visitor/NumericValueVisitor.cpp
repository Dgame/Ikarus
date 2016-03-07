//
// Created by Bjarne on 06.03.2016.
//

#include "NumericValueVisitor.hpp"
#include "NumericValue.hpp"

f32_t NumericValueVisitor::getNumber() const {
    if (std::isnan(_number)) {
        error("NAN");
    }

    return _number;
}

u32_t NumericValueVisitor::getIndex() const {
    const f32_t number = this->getNumber();
    if (number >= 0) {
        return static_cast<u32_t>(number);
    }

    throw "Negative Index";
}

void NumericValueVisitor::visit(const NumericValue* value) {
    _number = value->getValue();
}