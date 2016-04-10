#ifndef IKARUS_EVALUABLE_HPP
#define IKARUS_EVALUABLE_HPP

#include <iostream>

class EvalVisitor;

class Evaluable {
public:
    virtual void eval(std::ostream&) = 0;
};

#endif //IKARUS_EVALUABLE_HPP
