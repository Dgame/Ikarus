#include "VariableDeclaration.hpp"
#include "EvalVisitor.hpp"

VariableDeclaration::VariableDeclaration(const std::string& name, size_t id, Expression* exp) : Declaration(id, exp), _name(name) { }

VariableDeclaration::VariableDeclaration(const std::string& name, Expression* exp) : Declaration(exp), _name(name) { }

void VariableDeclaration::accept(EvalVisitor& ev) {
    ev.visit(this);
}

VariableDeclaration* VariableDeclaration::child(Expression* exp) const {
    return new VariableDeclaration(this->getName(), this->getId(), exp);
}