#ifndef IKARUS_ARRAY_EXPRESSION_HPP
#define IKARUS_ARRAY_EXPRESSION_HPP

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

    size_t getLength() const {
        return _values.size();
    }

    ArrayExpression* clone() const override;

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_ARRAY_EXPRESSION_HPP
