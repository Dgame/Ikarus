//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_VALUE_VISITOR_HPP
#define IKARUS_VALUE_VISITOR_HPP

class NumericValue;

class ArrayValue;

class ImmutableValueVisitor {
public:
    virtual void visit(const NumericValue*) = 0;
    virtual void visit(const ArrayValue*)   = 0;
};

#endif //IKARUS_VISITOR_HPP
