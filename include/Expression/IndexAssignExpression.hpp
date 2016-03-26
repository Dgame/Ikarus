#ifndef IKARUS_INDEXASSIGNEXPRESSION_HPP
#define IKARUS_INDEXASSIGNEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>

class IndexAssignExpression : public Expression {
private:
    std::unique_ptr<Expression> _index;
    std::unique_ptr<Expression> _value;
    ArrayExpression* _array;

public:
    explicit IndexAssignExpression(ArrayExpression*, Expression*, Expression*);

    IndexAssignExpression* clone() const override {
        return new IndexAssignExpression(_array, _index->clone(), _value->clone());
    }

    ArrayExpression* getArrayExpression() const {
        return _array;
    }

    Expression* getIndexExpression() {
        return _index.get();
    }

    Expression* getValueExpression() {
        return _value.get();
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_INDEXASSIGNEXPRESSION_HPP
