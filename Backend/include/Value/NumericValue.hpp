//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_INTEGER_HPP
#define IKARUS_INTEGER_HPP

#include "Value.hpp"
#include <types.hpp>
#include <util.hpp>

class NumericValue : public Value {
private:
    f32_t _value;

public:
    explicit NumericValue(f32_t);

    f32_t getValue() const {
        return _value;
    }

    virtual NumericValue* clone() const;

    virtual Compare compare(const Value*) const;

    virtual void accept(ImmutableValueVisitor*) const;
    virtual void accept(MutableValueVisitor*);

    virtual std::ostream& output(std::ostream& out) const {
        out << _value;

        return out;
    }
};

#endif //IKARUS_INTEGER_HPP
