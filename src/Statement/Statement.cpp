#include "Statement.hpp"

size_t Statement::ID = 0;

Statement::Statement(Expression* exp, Scope* scope) : _id(ID++), _expr(exp), _scope(scope) { }