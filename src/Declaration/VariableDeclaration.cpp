#include <Visitor/EvalVisitor.hpp>
#include "VariableDeclaration.hpp"
#include "AssignmentVisitor.hpp"

VariableDeclaration::VariableDeclaration(const std::string& name, size_t id, Expression* exp) : Declaration(id, exp), _name(name) { }

VariableDeclaration::VariableDeclaration(const std::string& name, Expression* exp) : Declaration(exp), _name(name) { }

VariableDeclaration* VariableDeclaration::child(Expression* exp) const {
    return new VariableDeclaration(this->getName(), this->getId(), exp);
}

void VariableDeclaration::eval(std::ostream& out) {
    AssignmentVisitor av;
    this->getExpression()->accept(av);

    EvalVisitor ev(out);
    this->getExpression()->accept(ev);

    for (auto& op : ev.getOperands()) {
        out << av.getAssignmentCommand() << " &" << this->getId() << ", ";
        op->print(std::cout);
        std::cout << '\n';
    }
}