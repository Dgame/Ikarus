//
// Created by Bjarne on 06.03.2016.
//

#include "NumericValueVisitor.hpp"
#include "NumericValue.hpp"

void NumericValueVisitor::visit(const NumericValue* value) {
    _number = value->getValue();
}
