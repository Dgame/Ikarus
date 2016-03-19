#ifndef IKARUS_EVALVISITOR_HPP
#define IKARUS_EVALVISITOR_HPP

#include <iostream>
#include "types.hpp"
#include "Visitor.hpp"

class VariableDeclaration;

class EvalVisitor : public Visitor {
private:
    enum State {
        NONE = 0,
        VARIABLE = 1
    };

    size_t _vid = 0;
    u32_t _state = NONE;

    std::ostream& _out;

    void setVariable(size_t vid) {
        _vid = vid;
        _state = VARIABLE;
    }

    bool hasVariable() const {
        return (_state & VARIABLE) != 0;
    }

    size_t popVariable() {
        _state &= ~VARIABLE;

        return _vid;
    }

public:
    explicit EvalVisitor(std::ostream&);

    virtual void visit(NumericExpression*);
    virtual void visit(ArrayExpression*);
    virtual void visit(VariableDeclaration*);
};

#endif //IKARUS_EVALVISITOR_HPP
