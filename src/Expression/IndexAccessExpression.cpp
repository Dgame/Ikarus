#include "IndexAccessExpression.hpp"

IndexAccessExpression::IndexAccessExpression(size_t vid, Expression* index) : VariableExpression(vid), _index(index) { }

IndexAccessExpression::IndexAccessExpression(VariableDeclaration* var, Expression* index) : VariableExpression(var), _index(index) {
    var->getExpression()->is<ArrayExpression>().ensure("Need ArrayExpression for index access");
}