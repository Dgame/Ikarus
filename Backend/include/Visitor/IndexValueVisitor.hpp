//
// Created by Bjarne on 06.03.2016.
//

#ifndef IKARUS_INDEXVALUEVISITOR_HPP
#define IKARUS_INDEXVALUEVISITOR_HPP

#include "NumericValueVisitor.hpp"

class IndexValueVisitor : public NumericValueVisitor {
public:
    u32_t getIndex() const;
};

#endif //IKARUS_INDEXVALUEVISITOR_HPP
