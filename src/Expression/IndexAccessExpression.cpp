#include "IndexAccessExpression.hpp"

IndexAccessExpression::IndexAccessExpression(ArrayExpression* array, Expression* index) : _array(array), _index(index) { }