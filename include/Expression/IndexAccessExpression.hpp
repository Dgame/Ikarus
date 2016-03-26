#ifndef IKARUS_INDEXACCESSEXPRESSION_HPP
#define IKARUS_INDEXACCESSEXPRESSION_HPP

#include "Expression.hpp"
#include <memory>

class IndexAccessExpression : public Expression {
private:
    std::unique_ptr<Expression> _index;
    ArrayExpression* _array;

public:
    explicit IndexAccessExpression(ArrayExpression*, Expression*);

    IndexAccessExpression* clone() const override {
        return new IndexAccessExpression(_array, _index->clone());
    }

    ArrayExpression* getArrayExpression() const {
        return _array;
    }

    Expression* getIndexExpression() {
        return _index.get();
    }

    void accept(Visitor& v) override {
        v.visit(this);
    }
};

#endif //IKARUS_INDEXACCESSEXPRESSION_HPP
