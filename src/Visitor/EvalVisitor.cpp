#include "EvalVisitor.hpp"
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
#include "MathEvalVisitor.hpp"
#include "Backend/VM/Value.hpp"
#include "Backend/VM/Variable.hpp"
#include "Backend/VM/Offset.hpp"

EvalVisitor::EvalVisitor(std::ostream& out) : _code(out), _out(out) { }

void EvalVisitor::eval(Expression* exp) {
    MathEvalVisitor mev(_out);
    exp->accept(mev);

    _operands.emplace_back(new Backend::Offset());
}

void EvalVisitor::visit(MultiplyExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(DivideExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(ModuloExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(AddExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(SubtractExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(IncrementExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(DecrementExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(VariableExpression* exp) {
    _operands.emplace_back(new Backend::Variable(exp->getVariableId()));
}

void EvalVisitor::visit(IndexAssignExpression* exp) {
    MathEvalVisitor mev(_out);
    exp->accept(mev);
}

void EvalVisitor::visit(IndexAccessExpression* exp) {
    MathEvalVisitor mev(_out);
    exp->accept(mev);

    _operands.emplace_back(new Backend::Offset());
}

void EvalVisitor::visit(NumericExpression* exp) {
    _operands.emplace_back(new Backend::Value<f32_t>(exp->getValue()));
}

void EvalVisitor::visit(ArrayExpression* exp) {
    for (size_t i = 0, max = exp->getLength(); i < max; i++) {
        exp->fetch(i)->accept(*this);
    }
}

void EvalVisitor::visit(LowerExpression* exp) {
//    this->binary(exp);
}

void EvalVisitor::visit(GreaterExpression* exp) {
//    _reversed = true;
    // reverse ordering
//    auto e = std::make_unique<LowerEqualExpression>(exp->getLeftExpression()->clone(),
//                                                    exp->getRightExpression()->clone());
//    e->accept(*this);
//    this->binary(exp);
}

void EvalVisitor::visit(LowerEqualExpression* exp) {
//    this->binary(exp);
}

void EvalVisitor::visit(GreaterEqualExpression* exp) {
//    _reversed = true;
    // reverse ordering
//    auto e = std::make_unique<LowerExpression>(exp->getLeftExpression()->clone(), exp->getRightExpression()->clone());
//    e->accept(*this);
//    this->binary(exp);
}

void EvalVisitor::visit(EqualExpression* exp) {
    this->eval(exp);
}

void EvalVisitor::visit(NotEqualExpression* exp) {
    this->eval(exp);
}
