//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_VALUE_HPP
#define IKARUS_VALUE_HPP

namespace ik {
    class IntegerValue;
    class ValueVisitor;

    class Value {
    public:
        virtual const IntegerValue* isInteger() const {
            return nullptr;
        }

        virtual Value* clone() const = 0;
        virtual void accept(ValueVisitor*) const = 0;
    };
}

#endif //IKARUS_VALUE_HPP
