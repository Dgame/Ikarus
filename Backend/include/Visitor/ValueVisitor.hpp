//
// Created by Bjarne on 07.03.2016.
//

#ifndef IKARUS_VISITOR_HPP
#define IKARUS_VISITOR_HPP

#include <type_traits>

enum class State {
    MUTABLE,
    IMMUTABLE
};

class NumericValue;

class ArrayValue;

template <State S>
class ValueVisitor {
public:
    using NV_T = typename std::conditional<S == State::IMMUTABLE, const NumericValue, NumericValue>::type;
    using AV_T = typename std::conditional<S == State::IMMUTABLE, const ArrayValue, ArrayValue>::type;

    virtual void visit(NV_T*) = 0;
    virtual void visit(AV_T*) = 0;
};

using MutableValueVisitor = ValueVisitor<State::MUTABLE>;
using ImmutableValueVisitor = ValueVisitor<State::IMMUTABLE>;

#endif //IKARUS_VISITOR_HPP
