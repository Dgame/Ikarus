//
// Created by Randy on 06.03.2016.
//

#include <OutputValueVisitor.hpp>
#include <NumericValue.hpp>
#include <util.hpp>

namespace ik {
    void OutputValueVisitor::visit(const NumericValue* value) {
        writeln("\tNUMERIC: ", value->getValue());
    }
}