#ifndef IKARUS_WHILESTATEMENT_HPP
#define IKARUS_WHILESTATEMENT_HPP

#include "Statement.hpp"
#include "EvalVisitor.hpp"

class WhileStatement : public Statement {
public:
    using Statement::Statement;

    void eval(std::ostream&) {

    }
};

#endif //IKARUS_WHILESTATEMENT_HPP
