#include <Visitor/EvalVisitor.hpp>
#include "VariableDeclaration.hpp"
#include "AssignmentCommandVisitor.hpp"

VariableDeclaration::VariableDeclaration(const std::string& name, size_t id, Expression* exp) : Declaration(id, exp), _name(name) { }

VariableDeclaration::VariableDeclaration(const std::string& name, Expression* exp) : Declaration(exp), _name(name) { }

VariableDeclaration* VariableDeclaration::descendant(Expression* exp) const {
    return new VariableDeclaration(this->getName(), this->getId(), exp);
}

void VariableDeclaration::eval(std::ostream& out) {
    AssignmentCommandVisitor cv;
    this->getExpression()->accept(cv);

    EvalVisitor ev(out);
    this->getExpression()->accept(ev);

    for (auto& op : ev.getOperands()) {
        out << cv.getAssignmentCommand() << " &" << this->getId() << ", ";
        op->print(std::cout);
        std::cout << '\n';
    }
}