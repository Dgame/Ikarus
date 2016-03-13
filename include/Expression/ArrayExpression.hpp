#ifndef IKARUS_ARRAYEXPRESSION_HPP
#define IKARUS_ARRAYEXPRESSION_HPP

#include "Expression.hpp"
#include "types.hpp"
#include <vector>
#include <memory>

class ArrayExpression : public Expression {
private:
    std::vector<std::unique_ptr<Expression>> _values;

    u32_t _index = 0;

public:
    explicit ArrayExpression(u32_t amount = 8);

    ArrayExpression* setIndex(u32_t index) {
        _index = index;

        return this;
    }

    u32_t getIndex() const {
        return _index;
    }

    Expression* fetch() {
        return _values.at(_index).get();
    }

    const Expression* fetch() const {
        return _values.at(_index).get();
    }

    u32_t getAmount() const {
        return _values.size();
    }

    void assign(Expression*);

    virtual ArrayExpression* clone() const;

    virtual void accept(Visitor&);
};

#endif //IKARUS_ARRAYEXPRESSION_HPP
