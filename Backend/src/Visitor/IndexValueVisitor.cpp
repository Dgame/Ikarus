//
// Created by Bjarne on 06.03.2016.
//

#include "IndexValueVisitor.hpp"

u32_t IndexValueVisitor::getIndex() const {
    const f32_t number = this->getNumber();
    if (number >= 0) {
        return static_cast<u32_t>(number);
    }

    throw "Negative Index";
}