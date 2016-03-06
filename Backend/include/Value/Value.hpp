//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_VALUE_HPP
#define IKARUS_VALUE_HPP

class MutableValueVisitor;

class ImmutableValueVisitor;

class Value {
public:
    virtual Value* clone() const = 0;
    virtual void accept(ImmutableValueVisitor*) const = 0;
    virtual void accept(MutableValueVisitor*)         = 0;
};

#endif //IKARUS_VALUE_HPP
