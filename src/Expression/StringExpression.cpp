#include "StringExpression.hpp"
#include "Visitor.hpp"

StringExpression::StringExpression(const std::string& str) : _value(str) { }

void StringExpression::accept(Visitor& v) {
    v.visit(this);
}