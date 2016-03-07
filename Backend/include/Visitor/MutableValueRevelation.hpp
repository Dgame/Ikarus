//
// Created by Bjarne on 07.03.2016.
//

#ifndef IKARUS_REVELATION_HPP
#define IKARUS_REVELATION_HPP

#include "MutableValueVisitor.hpp"
#include "types.hpp"

class MutableValueRevelation : public MutableValueVisitor {
public:
    union {
        NumericValue* numeric;
        ArrayValue* array;
    };

    virtual void visit(NumericValue* value) {
        this->numeric = value;
    }

    virtual void visit(ArrayValue* value) {
        this->array = value;
    }
};

#endif //IKARUS_REVELATION_HPP
