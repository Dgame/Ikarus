#include "OutputVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"

OutputVisitor::OutputVisitor(std::ostream& out) : _out(out) { }

void OutputVisitor::visit(NumericExpression* ie) {
    _out << ie->getNumber();
}

void OutputVisitor::visit(ArrayExpression* av) {
    const u32_t index = av->getIndex();

    _out << '[';
    for (u32_t i = 0; i < av->getAmount(); i++) {
        Expression* exp = av->setIndex(i)->fetch();
        if (exp) {
            exp->accept(*this);
        } else {
            _out << "NULL";
        }
        _out << ',';
    }
    _out << ']';

    av->setIndex(index);
}

void print(Expression* exp, bool nl) {
    OutputVisitor ov(std::cout);
    exp->accept(ov);

    if (nl)
        std::cout << std::endl;
}
