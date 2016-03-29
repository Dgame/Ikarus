#include "EvalVisitor.hpp"
#include "Backend/VM/Operand.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
#include "MultiplyExpression.hpp"
#include "DivideExpression.hpp"
#include "ModuloExpression.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "IncrementExpression.hpp"
#include "DecrementExpression.hpp"
#include "IndexAssignExpression.hpp"
#include "IndexAccessExpression.hpp"
#include "LowerExpression.hpp"
#include "GreaterExpression.hpp"
#include "LowerEqualExpression.hpp"
#include "GreaterEqualExpression.hpp"
#include "EqualExpression.hpp"
#include "NotEqualExpression.hpp"
#include "WhileStatement.hpp"

using Backend::Operand;

EvalVisitor::EvalVisitor(std::ostream& out) : _code(out), _out(out) { }

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
        _code.gen(cmd, Operand::Offset(_stack_offset - 1), false);
    }

    _out << ", ";

    if (rhs->isAtomic()) {
        rhs->accept(*this);
    } else {
        Operand::Offset(_stack_offset - 1).print(_out);
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
        _code.gen(cmd, Operand::Offset(_stack_offset - 1));
    } else {
        _out << std::endl;
    }

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
    Operand::Variable(exp->getVariableId()).print(_out);
}

void EvalVisitor::visit(IndexAssignExpression* exp) {
    _state &= ~VARIABLE;

    auto index = exp->getIndexExpression();
    if (index->isAtomic()) {
        _out << "set_index ";
    }

    index->accept(*this);

    if (!index->isAtomic()) {
        _code.gen("set_index", Operand::Offset(_stack_offset));
    }

    auto value = exp->getValueExpression();
    if (value->isAtomic()) {
        _code.gen("emplace", Operand::Variable(exp->getVariableId()));
    }

    value->accept(*this);
    if (!value->isAtomic()) {
        _code.gen("emplace", Operand::Variable(exp->getVariableId()), Operand::Offset(_stack_offset));
    }
}

void EvalVisitor::visit(IndexAccessExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        auto index = exp->getIndexExpression();
        if (index->isAtomic()) {
            _code.gen("fetch", Operand::Variable(exp->getVariableId()), false);
            _out << ", ";
        }

        index->accept(*this);

        if (!index->isAtomic()) {
            _code.gen("fetch", Operand::Variable(exp->getVariableId()), Operand::Offset(_stack_offset));
        } else {
            _out << std::endl;
        }
        _code.gen("assign", Operand::Variable(_vid), Operand::Offset(_stack_offset));
    } else {
        error("#4 Not implemented");
    }
}

void EvalVisitor::visit(NumericExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        _code.gen("assign", Operand::Variable(_vid), Operand::Number(exp->getNumber()));
    } else {
        _out << exp->getNumber();
    }
}

void EvalVisitor::visit(ArrayExpression* exp) {
    if (_state & VARIABLE) {
        _state &= ~VARIABLE;

        for (u32_t i = 0; i < exp->getAmount(); i++) {
            _code.gen("append", Operand::Variable(_vid), false);
            _out << ", ";
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
        _code.gen("pop", Operand::Variable(vd->getId()));
        _stack_offset--;
    }
}

void EvalVisitor::visit(LowerExpression* exp) {
    this->math("is_lower", exp);
}

void EvalVisitor::visit(GreaterExpression* exp) {
    // reverse ordering
    auto e = std::make_unique<LowerExpression>(exp->getRightExpression()->clone(), exp->getLeftExpression()->clone());
    e->accept(*this);
}

void EvalVisitor::visit(LowerEqualExpression* exp) {
    this->math("is_lower_or_equal", exp);
}

void EvalVisitor::visit(GreaterEqualExpression* exp) {
    // reverse ordering
    auto e = std::make_unique<LowerEqualExpression>(exp->getRightExpression()->clone(), exp->getLeftExpression()->clone());
    e->accept(*this);
}

void EvalVisitor::visit(EqualExpression* exp) {
    this->math("is_equal", exp);
}

void EvalVisitor::visit(NotEqualExpression* exp) {
    this->math("is_not_equal", exp);
}

void EvalVisitor::visit(WhileStatement* stmt) {
    const std::string start = _code.label(stmt->getId());
    const std::string end = _code.label(stmt->getId());

    _code.genLabel(start);
    stmt->getExpression()->accept(*this);
    _code.gen("goto_if", end);

    stmt->getScope()->eval(_out);

    _code.gen("goto", start);
    _code.genLabel(end);
}
