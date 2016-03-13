#ifndef IKARUS_VISITABLE_HPP
#define IKARUS_VISITABLE_HPP

class Visitor;

class Visitable {
public:
    virtual void accept(Visitor&) = 0;
};

#endif //IKARUS_VISITABLE_HPP
