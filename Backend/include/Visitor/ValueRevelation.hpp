//
// Created by Bjarne on 07.03.2016.
//

#ifndef IKARUS_REVELATION_HPP
#define IKARUS_REVELATION_HPP

#include "ValueVisitor.hpp"
#include "types.hpp"

template <State S>
class ValueRevelation : public ValueVisitor<S> {
public:
    using NV_T = typename ValueVisitor<S>::NV_T;
    using AV_T = typename ValueVisitor<S>::AV_T;

    NV_T* numeric = nullptr;
    AV_T* array = nullptr;

    virtual void visit(NV_T* value) {
        this->numeric = value;
    }

    virtual void visit(AV_T* value) {
        this->array = value;
    }
};

using MutableValueRevelation = ValueRevelation<State::MUTABLE>;
using ImmutableValueRevelation = ValueRevelation<State::IMMUTABLE>;

#endif //IKARUS_REVELATION_HPP
