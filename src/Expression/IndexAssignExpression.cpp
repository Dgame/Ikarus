#include "IndexAssignExpression.hpp"

IndexAssignExpression::IndexAssignExpression(ArrayExpression* array, Expression* index, Expression* value) : _array(array), _index(index),
                                                                                                             _value(value) { }