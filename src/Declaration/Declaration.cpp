#include "Declaration.hpp"

size_t Declaration::ID = 0;

Declaration::Declaration(size_t id, Expression* exp) : _id(id), _expr(exp) { }

Declaration::Declaration(Expression* exp) : Declaration(ID++, exp) { }
