#include "ArrayExpression.hpp"
#include "Visitor.hpp"

ArrayExpression::ArrayExpression(u32_t amount) : _values(amount) { }

void ArrayExpression::assign(Expression* exp) {
    if (_index >= this->getAmount()) {
        _values.resize((_index + 1) * 2);
    }

    _values.at(_index).reset(exp);
    _index++;
}

ArrayExpression* ArrayExpression::clone() const {
    ArrayExpression* ae = new ArrayExpression();

    for (auto& item : _values) {
        if (item) {
            ae->assign(item->clone());
        }
    }

    return ae;
}

void ArrayExpression::accept(Visitor& v) {
    v.visit(this);
}