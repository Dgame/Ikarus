#ifndef IKARUS_DECLARATION_HPP
#define IKARUS_DECLARATION_HPP

#include "Expression.hpp"
#include "Frontend/Evaluable.hpp"
#include "types.hpp"
#include <memory>

class Declaration : public Evaluable {
private:
    const size_t _id = 0;
    std::unique_ptr<Expression> _expr;

    static size_t& ID() {
        static size_t id = 0;

        return id;
    }

protected:
    explicit Declaration(size_t, Expression*);

public:
    explicit Declaration(Expression*);

    size_t getId() const {
        return _id;
    }

    Expression* getExpression() {
        return _expr.get();
    }

    const Expression* getExpression() const {
        return _expr.get();
    }

    virtual Declaration* descendant(Expression*) const = 0;
};

#endif //IKARUS_DECLARATION_HPP
