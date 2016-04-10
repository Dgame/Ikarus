#include "MathEvalVisitor.hpp"
#include "NumericExpression.hpp"
#include "NotExpression.hpp"
#include "NegateExpression.hpp"
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
#include "Backend/VM/Offset.hpp"
#include "Backend/VM/Value.hpp"
#include "Backend/VM/Variable.hpp"

MathEvalVisitor::MathEvalVisitor(std::ostream& out) : _out(out) { }

void MathEvalVisitor::binary(const std::string& cmd, BinaryExpression* exp) {
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
        _out << cmd << ' ';
        Backend::Offset().print(_out);
    }

    _out << ", ";

    if (rhs->isAtomic()) {
        rhs->accept(*this);
    } else {
        Backend::Offset().print(_out);
    }

    _out << '\n';
}

void MathEvalVisitor::unary(const std::string& cmd, UnaryExpression* exp) {
    Expression* e = exp->getExpression();
    if (e->isAtomic()) {
        _out << cmd << ' ';
    }

    e->accept(*this);

    if (!e->isAtomic()) {
        std::cout << cmd << ' ';
        Backend::Offset().print(_out);
    } else {
        _out << '\n';
    }
}

void MathEvalVisitor::visit(NumericExpression* exp) {
    Backend::Value<f32_t>(exp->getValue()).print(_out);
}

void MathEvalVisitor::visit(NotExpression* exp) {
    this->unary("not", exp);
}

void MathEvalVisitor::visit(NegateExpression* exp) {
    this->unary("negate", exp);
}

void MathEvalVisitor::visit(VariableExpression* exp) {
    Backend::Variable(exp->getVariableId()).print(_out);
}

void MathEvalVisitor::visit(AddExpression* exp) {
    this->binary("add", exp);
}

void MathEvalVisitor::visit(SubtractExpression* exp) {
    this->binary("sub", exp);
}

void MathEvalVisitor::visit(MultiplyExpression* exp) {
    this->binary("mul", exp);
}

void MathEvalVisitor::visit(DivideExpression* exp) {
    this->binary("div", exp);
}

void MathEvalVisitor::visit(ModuloExpression* exp) {
    this->binary("mod", exp);
}

void MathEvalVisitor::visit(IncrementExpression* exp) {
    this->unary("inc", exp);
}

void MathEvalVisitor::visit(DecrementExpression* exp) {
    this->unary("dec", exp);
}

// TODO
void MathEvalVisitor::visit(IndexAssignExpression* exp) {
    auto index = exp->getIndexExpression();

    if (index->isAtomic()) {
        _out << "set_index ";
    }

    index->accept(*this);

    if (!index->isAtomic()) {
        _out << "set_index ";
        Backend::Offset().print(_out);
    }

    _out << '\n';
}

void MathEvalVisitor::visit(IndexAccessExpression* exp) {
    auto index = exp->getIndexExpression();

    if (index->isAtomic()) {
        _out << "fetch ";
        Backend::Variable(exp->getVariableId()).print(_out);
        _out << ", ";
    }

    index->accept(*this);

    if (!index->isAtomic()) {
        _out << "fetch ";
        Backend::Variable(exp->getVariableId()).print(_out);
        Backend::Offset().print(_out);
    } else {
        _out << '\n';
    }
}

