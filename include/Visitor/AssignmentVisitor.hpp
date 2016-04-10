#ifndef IKARUS_ASSIGNMENT_VISITOR_HPP
#define IKARUS_ASSIGNMENT_VISITOR_HPP

#include "Visitor.hpp"
#include <string>

class AssignmentVisitor : public Visitor {
private:
    std::string _cmd = "assign";

public:
    const std::string& getAssignmentCommand() const {
        return _cmd;
    }

    void visit(ArrayExpression*) override {
        _cmd = "append";
    }
};

#endif