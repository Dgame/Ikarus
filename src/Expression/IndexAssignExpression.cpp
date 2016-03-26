#include "IndexAssignExpression.hpp"

IndexAssignExpression::IndexAssignExpression(size_t vid, Expression* index, Expression* value) : VariableExpression(vid),
                                                                                                 _index(index),
                                                                                                 _value(value) { }

IndexAssignExpression::IndexAssignExpression(VariableDeclaration* var, Expression* index, Expression* value) : VariableExpression(var),
                                                                                                               _index(index),
                                                                                                               _value(value) {
    var->getExpression()->is<ArrayExpression>().ensure("Need ArrayExpression for index assign");
}