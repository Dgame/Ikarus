#include "OutputVisitor.hpp"
#include "StringExpression.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"

OutputVisitor::OutputVisitor(std::ostream& out) : _out(out) { }

void OutputVisitor::visit(NumericExpression* exp) {
    _out << exp->getValue();
}

void OutputVisitor::visit(StringExpression* exp) {
    _out << exp->getValue();
}

void OutputVisitor::visit(ArrayExpression* exp) {
    _out << '[';
    for (u32_t i = 0; i < exp->getLength(); i++) {
        Expression* item = exp->fetch(i);
        if (item) {
            item->accept(*this);
        } else {
            _out << "NULL";
        }

        if ((i + 1) < exp->getLength()) {
            _out << ", ";
        }
    }
    _out << ']';
}

void print(Expression* exp, bool nl) {
    OutputVisitor ov(std::cout);
    exp->accept(ov);

    if (nl)
        std::cout << '\n';
}
