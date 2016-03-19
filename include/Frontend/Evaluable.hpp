#ifndef IKARUS_EVALUABLE_HPP
#define IKARUS_EVALUABLE_HPP

class EvalVisitor;

class Evaluable {
public:
    virtual void accept(EvalVisitor&) = 0;
};

#endif //IKARUS_EVALUABLE_HPP
