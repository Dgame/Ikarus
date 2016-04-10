#include "Frontend/Scope.hpp"
#include "VariableDeclaration.hpp"
#include "EvalVisitor.hpp"

Scope::Scope(Scope* sc) : _predecessor(sc) { }

void Scope::addVariable(VariableDeclaration* vd) {
    _variables[vd->getName()] = vd;

    this->add(vd);
}

void Scope::add(Evaluable* e) {
    _evals.emplace_back(e);
}

VariableDeclaration* Scope::findVariable(const std::string& name) {
    auto it = _variables.find(name);
    if (it != _variables.end()) {
        return it->second;
    }

    if (_predecessor) {
        return _predecessor->findVariable(name);
    }

    return nullptr;
}

void Scope::eval(std::ostream& out) {
    for (auto& e : _evals) {
        e->eval(out);
    }
}