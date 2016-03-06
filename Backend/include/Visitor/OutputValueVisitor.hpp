//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_OUTPUT_VALUE_VISITOR_HPP
#define IKARUS_OUTPUT_VALUE_VISITOR_HPP

#include "ImmutableValueVisitor.hpp"

class OutputValueVisitor : public ImmutableValueVisitor {
    virtual void visit(const NumericValue*);
    virtual void visit(const ArrayValue*);
};

#endif //IKARUS_OUTPUTVISITOR_HPP
