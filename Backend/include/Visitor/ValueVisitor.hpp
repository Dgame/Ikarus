//
// Created by Randy on 06.03.2016.
//

#ifndef IKARUS_VALUE_VISITOR_HPP
#define IKARUS_VALUE_VISITOR_HPP

namespace ik {
    class IntegerValue;
    class Decimal;
    class Boolean;
    class String;

    class ValueVisitor {
    public:
        virtual void visit(const IntegerValue*) = 0;

        //virtual void visit(const Decimal*) = 0;

        //virtual void visit(const Boolean*) = 0;

        //virtual void visit(const String*) = 0;
    };
}

#endif //IKARUS_VISITOR_HPP
