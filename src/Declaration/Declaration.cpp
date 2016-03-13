#include "Declaration.hpp"

u32_t Declaration::ID = 0;

Declaration::Declaration(Expression* exp) : _id(ID++), _expr(exp) { }