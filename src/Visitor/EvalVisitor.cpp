#include "EvalVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
#include "AddExpression.hpp"
#include "MultiplyExpression.hpp"
#include "VariableDeclaration.hpp"

EvalVisitor::EvalVisitor(std::ostream& out) : _out(out) { }

void EvalVisitor::math(const std::string& cmd, BinaryExpression* exp) {
    Expression* lhs = exp->getLeftExpression();
    Expression* rhs = exp->getRightExpression();

    if (!rhs->isAtomic()) {
        rhs->accept(*this);
    }

    if (lhs->isAtomic()) {
        _out << cmd << ' ';
    }

    lhs->accept(*this);

    if (!lhs->isAtomic()) {
        _out << cmd << " ~" << (_stack_offset - 1);
    }

    _out << ", ";

    if (rhs->isAtomic()) {
        rhs->accept(*this);
    } else {
        _out << '~' << (_stack_offset - 1);
    }

    _out << std::endl;

    _stack_offset++;
}

void EvalVisitor::visit(MultiplyExpression* exp) {
    this->math("mul", exp);
}

void EvalVisitor::visit(AddExpression* exp) {
    this->math("add", exp);
}

void EvalVisitor::visit(NumericExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        _out << "assign &" << _vid << ", " << exp->getNumber() << std::endl;
    } else {
        _out << exp->getNumber();
    }
}

void EvalVisitor::visit(ArrayExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        for (u32_t i = 0; i < exp->getAmount(); i++) {
            _out << "append &" << _vid << ", ";
            exp->fetch(i)->accept(*this);
            _out << std::endl;
        }
    } else {
        error("Not implemented");
    }
}

void EvalVisitor::visit(VariableDeclaration* vd) {
    Expression* exp = vd->getExpression();
    if (exp->isAtomic()) {
        _vid = vd->getId();
        _state = VARIABLE;
    }

    vd->getExpression()->accept(*this);

    if (!exp->isAtomic()) {
        _out << "pop &" << vd->getId() << std::endl;
        _stack_offset--;
    }
}