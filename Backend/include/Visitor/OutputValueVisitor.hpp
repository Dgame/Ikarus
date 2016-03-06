//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_OUTPUT_VALUE_VISITOR_HPP
#define IKARUS_OUTPUT_VALUE_VISITOR_HPP

#include "ValueVisitor.hpp"

namespace ik {
    class OutputValueVisitor : public ValueVisitor {
        virtual void visit(const NumericValue*);
    };
}

#endif //IKARUS_OUTPUTVISITOR_HPP
