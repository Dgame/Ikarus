//
// Created by Randy on 06.03.2016.
//

#include "OutputValueVisitor.hpp"
#include "NumericValue.hpp"
#include "ArrayValue.hpp"

void OutputValueVisitor::visit(const NumericValue* value) {
    writeln("\tNUMERIC: ", value->getValue());
}

void OutputValueVisitor::visit(const ArrayValue* values) {
    std::cout << '[';
    for (auto& value : values->getValues()) {
        std::cout << "\t";
        value->accept(this);
    }
    std::cout << ']' << std::endl;
}
