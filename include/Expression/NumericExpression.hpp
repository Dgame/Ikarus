#ifndef IKARUS_NUMERICEXPRESSION_HPP
#define IKARUS_NUMERICEXPRESSION_HPP

#include <type_traits>
#include "types.hpp"
#include "Expression.hpp"

class NumericExpression : public Expression  {
private:
    f32_t _number = 0;

public:
    explicit NumericExpression(f32_t);

    f32_t getNumber() const {
        return _number;
    }

    template <typename T>
    T getAs() const {
        static_assert(std::is_convertible<T, i32_t>::value, "T must derive from int");

        return static_cast<T>(_number);
    }

    virtual NumericExpression* clone() const override{
        return new NumericExpression(_number);
    }

    virtual void accept(Visitor&) override;
};

#endif //IKARUS_NUMERICEXPRESSION_HPP
