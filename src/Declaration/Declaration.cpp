#include "Declaration.hpp"

size_t Declaration::ID = 0;

Declaration::Declaration(Expression* exp) : _id(ID++), _expr(exp) { }
