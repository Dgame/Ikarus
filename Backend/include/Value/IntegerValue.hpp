//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_INTEGER_HPP
#define IKARUS_INTEGER_HPP

#include "Value.hpp"

namespace ik {
    class IntegerValue : public Value {
    private:
        int _value;

    public:
        explicit IntegerValue(int);

        int getValue() const {
            return _value;
        }

        virtual const IntegerValue* isInteger() const {
            return this;
        }

        virtual IntegerValue* clone() const;

        virtual void accept(ValueVisitor*) const;
    };
}

#endif //IKARUS_INTEGER_HPP
