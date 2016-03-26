#include "EvalVisitor.hpp"
#include "NumericExpression.hpp"
#include "BoolExpression.hpp"
#include "ArrayExpression.hpp"
#include "MultiplyExpression.hpp"
#include "DivideExpression.hpp"
#include "ModuloExpression.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "IncrementExpression.hpp"
#include "DecrementExpression.hpp"
#include "IndexAssignExpression.hpp"

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

void EvalVisitor::math(const std::string& cmd, UnaryExpression* exp) {
    Expression* e = exp->getExpression();

    if (e->isAtomic()) {
        _out << cmd << ' ';
    }

    e->accept(*this);

    if (!e->isAtomic()) {
        _out << cmd << " ~" << (_stack_offset - 1);
    }
    _out << std::endl;

    _stack_offset++;
}

void EvalVisitor::visit(MultiplyExpression* exp) {
    this->math("mul", exp);
}

void EvalVisitor::visit(DivideExpression* exp) {
    this->math("div", exp);
}

void EvalVisitor::visit(ModuloExpression* exp) {
    this->math("mod", exp);
}

void EvalVisitor::visit(AddExpression* exp) {
    this->math("add", exp);
}

void EvalVisitor::visit(SubtractExpression* exp) {
    this->math("sub", exp);
}

void EvalVisitor::visit(IncrementExpression* exp) {
    this->math("inc", exp);
}

void EvalVisitor::visit(DecrementExpression* exp) {
    this->math("dec", exp);
}

void EvalVisitor::visit(VariableExpression* exp) {
    _out << '&' << exp->getVariableId();
}

void EvalVisitor::visit(IndexAssignExpression* exp) {
    _state &= ~VARIABLE;

    auto index = exp->getIndexExpression();

    if (index->isAtomic()) {
        _out << "set_index ";
    }

    index->accept(*this);

    if (!index->isAtomic()) {
        _out << "set_index ~" << _stack_offset;
    }
    _out << std::endl;

    auto value = exp->getValueExpression();
    if (value->isAtomic()) {
        _out << "emplace &" << exp->getVariableId() << ", ";
    }

    value->accept(*this);

    if (!value->isAtomic()) {
        _out << "emplace &" << exp->getVariableId() << ", ~" << _stack_offset;
    }
    _out << std::endl;
}

void EvalVisitor::visit(NumericExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        _out << "assign &" << _vid << ", " << exp->getNumber() << std::endl;
    } else {
        _out << exp->getNumber();
    }
}

void EvalVisitor::visit(BoolExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        _out << "assign &" << _vid << ", " << static_cast<i32_t>(exp->getValue()) << std::endl;
    } else {
        _out << static_cast<i32_t>(exp->getValue());
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
        error("#3 Not implemented");
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