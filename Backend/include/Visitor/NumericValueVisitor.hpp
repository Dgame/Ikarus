//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_NUMERICVALUEVISITOR_HPP
#define IKARUS_NUMERICVALUEVISITOR_HPP

#include "ImmutableValueVisitor.hpp"
#include <cmath>
#include "types.hpp"

class NumericValueVisitor : public ImmutableValueVisitor {
private:
    f32_t _number = NAN;

public:
    f32_t getNumber() const;
    u32_t getIndex() const;

    virtual void visit(const NumericValue*);

    virtual void visit(const ArrayValue*) { }
};

#endif //IKARUS_NUMERICVALUEVISITOR_HPP
