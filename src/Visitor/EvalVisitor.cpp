#include "EvalVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
#include "VariableDeclaration.hpp"

EvalVisitor::EvalVisitor(std::ostream& out) : _out(out) { }

void EvalVisitor::visit(NumericExpression* exp) {
    if (this->hasVariable()) {
        const size_t vid = this->popVariable();

        _out << "assign &" << vid << ", " << exp->getNumber() << std::endl;
    } else {
        _out << exp->getNumber();
    }
}

void EvalVisitor::visit(ArrayExpression* exp) {
    if (this->hasVariable()) {
        const size_t vid = this->popVariable();

        for (u32_t i = 0; i < exp->getAmount(); i++) {
            _out << "append &" << vid << ", ";
            exp->fetch(i)->accept(*this);
            _out << std::endl;
        }
    } else {
        error("Not implemented");
    }
}

void EvalVisitor::visit(VariableDeclaration* vd) {
    this->setVariable(vd->getId());
    vd->getExpression()->accept(*this);
}