#include "Declaration.hpp"

Declaration::Declaration(size_t id, Expression* exp) : _id(id), _expr(exp) { }

Declaration::Declaration(Expression* exp) : Declaration(ID()++, exp) { }
