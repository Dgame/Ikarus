//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_INTEGER_HPP
#define IKARUS_INTEGER_HPP

#include "Value.hpp"
#include <types.hpp>
#include <util.hpp>

namespace ik {
    class NumericValue : public Value {
    private:
        f32_t _value;

    public:
        explicit NumericValue(f32_t);

        template <typename T>
        T get() const;

        f32_t getValue() const {
            return _value;
        }

        virtual const NumericValue* isNumeric() const {
            return this;
        }

        virtual NumericValue* clone() const;

        virtual void accept(ValueVisitor*) const;
    };

    template <typename T>
    T NumericValue::get() const {
        return static_cast<T>(_value);
    }
}

#endif //IKARUS_INTEGER_HPP
