#include "IndexAccessExpression.hpp"

IndexAccessExpression::IndexAccessExpression(VariableDeclaration* var, Expression* index) : VariableExpression(var), _index(index) {
    var->getExpression()->is<ArrayExpression>().ensure("Need ArrayExpression for index access");
}