#ifndef IKARUS_SCOPE_HPP
#define IKARUS_SCOPE_HPP

#include <map>
#include <vector>
#include <memory>
#include "Evaluable.hpp"

class VariableDeclaration;

class Scope {
private:
    Scope* _predecessor = nullptr;
    std::map<std::string, VariableDeclaration*> _variables;
    std::vector<std::unique_ptr<Evaluable>> _evals;

public:
    explicit Scope(Scope*);

    Scope* getPredecessor() {
        return _predecessor;
    }

    void addVariable(VariableDeclaration*);
    void add(Evaluable*);

    const VariableDeclaration* findVariable(const std::string&);

    void eval(std::ostream&);
};

#endif //IKARUS_SCOPE_HPP
