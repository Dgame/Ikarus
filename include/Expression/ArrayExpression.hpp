#ifndef IKARUS_ARRAYEXPRESSION_HPP
#define IKARUS_ARRAYEXPRESSION_HPP

#include "Expression.hpp"
#include "types.hpp"
#include <vector>
#include <memory>

class ArrayExpression : public Expression {
private:
    std::vector<std::unique_ptr<Expression>> _values;

public:
    void append(Expression* exp) {
        _values.emplace_back(exp);
    }

    void emplace(u32_t, Expression*);

    Expression* fetch(u32_t index) {
        return _values.at(index).get();
    }

    u32_t getAmount() const {
        return _values.size();
    }

    virtual ArrayExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_ARRAYEXPRESSION_HPP
