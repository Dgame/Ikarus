#ifndef IKARUS_DECLARATION_HPP
#define IKARUS_DECLARATION_HPP

#include "Expression.hpp"
#include "Visitable.hpp"
#include "types.hpp"
#include <memory>

class Declaration {
private:
    static u32_t ID;

    u32_t _id = 0;

    std::unique_ptr<Expression> _expr;

public:
    explicit Declaration(Expression*);

    u32_t getId() const {
        return _id;
    }

    Expression* getExpression() {
        return _expr.get();
    }
};

#endif //IKARUS_DECLARATION_HPP
