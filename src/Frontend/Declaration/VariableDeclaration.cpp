#include "VariableDeclaration.hpp"
#include "EvalVisitor.hpp"

VariableDeclaration::VariableDeclaration(const std::string& name, Expression* exp) : Declaration(exp), _name(name) { }

void VariableDeclaration::accept(EvalVisitor& ev) {
    ev.visit(this);
}