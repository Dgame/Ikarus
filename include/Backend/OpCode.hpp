#ifndef IKARUS_OPCODE_HPP
#define IKARUS_OPCODE_HPP

#include <memory>
#include "Expression.hpp"

class OpCode {
public:
    enum Type {
        VARIABLE,
        OFFSET,
        VALUE
    };

private:
    Type _type;

    std::unique_ptr<Expression> _expr;

public:
    explicit OpCode(Type, Expression*);

    Type getType() const {
        return _type;
    }

    Expression* getExpression() {
        return _expr.get();
    }
};

#endif //IKARUS_OPCODE_HPP
