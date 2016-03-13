#ifndef IKARUS_INTERPRETER_HPP
#define IKARUS_INTERPRETER_HPP

#include <string>
#include <vector>
#include <memory>

#include "types.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

class Parser;

class Interpreter {
private:
    std::vector<std::unique_ptr<Expression>> _variables;
    std::vector<std::unique_ptr<Expression>> _stack;

    u32_t _stack_offset = 0;

    void assignVariable(u32_t, Expression*);
    void pushStack(Expression*);
    auto popStack();

    Expression* fetchStack(u32_t);
    Expression* fetchVariable(u32_t);

    bool interpret(Parser&);

    Expression* resolveExpression(OpCode*);
    u32_t getIndexOf(OpCode*);

    Expression* resolveVariable(OpCode*);

    template <typename T>
    Expression* resolveOrMakeVariable(OpCode*);

    void print(Instruction*);
    void assign(Instruction*);
    void append(Instruction*);
    void emplace(Instruction*);
    void fetchDim(Instruction*);
    void fetch(Instruction*);
    void pop(Instruction*);
    void push(Instruction*);

    void math(Instruction*);

    Expression* makeExpression(Instruction*);

public:
    explicit Interpreter(const std::string&);
};

#endif //IKARUS_INTERPRETER_HPP