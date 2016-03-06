//
// Created by Randy on 06.03.2016.
//

#include "../../include/Visitor/OutputValueVisitor.hpp"
#include "../../include/Value/IntegerValue.hpp"
#include "../../include/util.hpp"

namespace ik {
    void OutputValueVisitor::visit(const IntegerValue* value) {
        writeln("\tINTEGER: ", value->getValue());
    }
}