#include "ArrayExpression.hpp"

void ArrayExpression::emplace(u32_t index, Expression* exp) {
    if (index >= this->getLength()) {
        _values.resize(index + 1);
    }

    _values.at(index).reset(exp);
}

ArrayExpression* ArrayExpression::clone() const {
    ArrayExpression* ae = new ArrayExpression();

    for (auto& item : _values) {
        if (item) {
            ae->append(item->clone());
        }
    }

    return ae;
}
