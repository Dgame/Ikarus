//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_ARRAYVALUE_HPP
#define IKARUS_ARRAYVALUE_HPP

#include "Value.hpp"
#include "types.hpp"
#include <vector>
#include <memory>

class ArrayValue : public Value {
private:
    u32_t _index = 0;

    std::vector<std::unique_ptr<const Value>> _values;

public:
    explicit ArrayValue(u32_t amount = 8);

    void setIndex(u32_t index) {
        _index = index;
    }

    void assign(const Value*);

    u32_t getAmount() const {
        return _values.size();
    }

    auto& getValues() {
        return _values;
    }

    auto& getValues() const {
        return _values;
    }

    virtual ArrayValue* clone() const;

    virtual void accept(ImmutableValueVisitor*) const;
    virtual void accept(MutableValueVisitor*);
};

#endif //IKARUS_ARRAYVALUE_HPP
