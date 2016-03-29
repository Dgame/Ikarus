#ifndef IKARUS_STATEMENT_HPP
#define IKARUS_STATEMENT_HPP

#include <memory>
#include "Expression.hpp"
#include "Frontend/Evaluable.hpp"
#include "Frontend/Scope.hpp"

class Scope;

class Statement : public Evaluable {
private:
    static size_t ID;

    const size_t _id = 0;
    std::unique_ptr<Expression> _expr;
    std::unique_ptr<Scope> _scope;

public:
    explicit Statement(Expression*, Scope*);

    size_t getId() const {
        return _id;
    }

    Expression* getExpression() {
        return _expr.get();
    }

    Scope* getScope() {
        return _scope.get();
    }
};

#endif //IKARUS_STATEMENT_HPP
