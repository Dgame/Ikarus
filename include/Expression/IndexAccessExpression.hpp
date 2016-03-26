#ifndef IKARUS_INDEXACCESSEXPRESSION_HPP
#define IKARUS_INDEXACCESSEXPRESSION_HPP

#include "VariableExpression.hpp"
#include <memory>

class IndexAccessExpression : public VariableExpression {
private:
    std::unique_ptr<Expression> _index;

public:
    explicit IndexAccessExpression(VariableDeclaration*, Expression*);

    IndexAccessExpression* clone() const override {
        return new IndexAccessExpression(this->getVariableDeclaration(), _index->clone());
    }

    Expression* getIndexExpression() {
        return _index.get();
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_INDEXACCESSEXPRESSION_HPP
