//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_VALUE_HPP
#define IKARUS_VALUE_HPP

#include <ostream>
#include "types.hpp"
#include "ValueVisitor.hpp"

enum class Compare;

class Value {
public:
    virtual Value* clone() const = 0;

    virtual Compare compare(const Value*) const = 0;

    virtual void accept(ImmutableValueVisitor*) const = 0;
    virtual void accept(MutableValueVisitor*)         = 0;

    virtual std::ostream& output(std::ostream&) const = 0;
};

#endif //IKARUS_VALUE_HPP
