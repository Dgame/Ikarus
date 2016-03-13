#ifndef IKARUS_NUMERICEXPRESSION_HPP
#define IKARUS_NUMERICEXPRESSION_HPP

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

    virtual NumericExpression* clone() const {
        return new NumericExpression(_number);
    }

    virtual void accept(Visitor&);
};

#endif //IKARUS_NUMERICEXPRESSION_HPP
