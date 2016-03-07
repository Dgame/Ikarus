//
// Created by Bjarne on 07.03.2016.
//

#ifndef IKARUS_IMMUTABLEVALUEREVELATION_HPP
#define IKARUS_IMMUTABLEVALUEREVELATION_HPP

#include "ImmutableValueVisitor.hpp"
#include "types.hpp"

class ImmutableValueRevelation : public ImmutableValueVisitor {
public:
    union {
        const NumericValue* numeric;
        const ArrayValue* array;
    };

    virtual void visit(const NumericValue* value) {
        this->numeric = value;
    }

    virtual void visit(const ArrayValue* value) {
        this->array = value;
    }
};

#endif //IKARUS_IMMUTABLEVALUEREVELATION_HPP
