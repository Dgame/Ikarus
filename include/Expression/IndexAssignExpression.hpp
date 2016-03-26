#ifndef IKARUS_INDEXASSIGNEXPRESSION_HPP
#define IKARUS_INDEXASSIGNEXPRESSION_HPP

#include "VariableExpression.hpp"
#include <memory>

class IndexAssignExpression : public VariableExpression {
private:
    std::unique_ptr<Expression> _index;
    std::unique_ptr<Expression> _value;

    explicit IndexAssignExpression(size_t, Expression*, Expression*);

public:
    explicit IndexAssignExpression(VariableDeclaration*, Expression*, Expression*);

    IndexAssignExpression* clone() const override {
        return new IndexAssignExpression(this->getVariableId(), _index->clone(), _value->clone());
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
