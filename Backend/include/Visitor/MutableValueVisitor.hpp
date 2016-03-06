//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_MUTABLEVALUEVISITOR_HPP
#define IKARUS_MUTABLEVALUEVISITOR_HPP

class NumericValue;

class ArrayValue;

class MutableValueVisitor {
public:
    virtual void visit(NumericValue*) = 0;
    virtual void visit(ArrayValue*)   = 0;
};

#endif //IKARUS_MUTABLEVALUEVISITOR_HPP
