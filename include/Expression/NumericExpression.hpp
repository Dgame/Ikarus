#ifndef IKARUS_NUMERIC_EXPRESSION_HPP
#define IKARUS_NUMERIC_EXPRESSION_HPP

#include <type_traits>
#include "types.hpp"
#include "Expression.hpp"

class NumericExpression : public Expression {
private:
    f32_t _value = 0;

public:
    explicit NumericExpression(f32_t value) : _value(value) { }

    f32_t getNumber() const {
        return _value;
    }

    template <typename T>
    T getAs() const {
        static_assert(std::is_convertible<T, i32_t>::value, "T must derive from int");

        return static_cast<T>(_value);
    }

    NumericExpression* clone() const override {
        return new NumericExpression(_value);
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_NUMERIC_EXPRESSION_HPP
