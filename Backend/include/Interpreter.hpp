//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_INTERPRETER_HPP
#define IKARUS_INTERPRETER_HPP

#include <string>
#include <vector>
#include <memory>
#include "Command.hpp"
#include <Value.hpp>
#include "types.hpp"

class OpCode;

class Expression;

class Interpreter {
private:
    std::vector<std::unique_ptr<Value>> _variables;
    std::vector<std::unique_ptr<Value>> _stack;

    u32_t _stack_offset = 0;

    u32_t getStackOffset() const {
        return _stack_offset;
    }

    void assignVariable(u32_t, Value*);

    void pushStack(Value*);
    Value* popStack();

    Value      * fetchVariable(u32_t) const;
    const Value* fetchStack(u32_t) const;
    const Value* getValue(const OpCode*) const;

    void interpret(const std::vector<std::unique_ptr<Command>>&);

    void assign(const Command*);
    void push(const Command*);
    void pop(const Command*);
    void print(const Command*);
    void append(const Command*);
    void index(const Command*);
    void fetch(const Command*);

    void add(const Command*);
    void sub(const Command*);
    void mul(const Command*);
    void div(const Command*);
    void mod(const Command*);
    void op_not(const Command*);
    void op_neg(const Command*);
    void op_inc(const Command*);
    void op_dec(const Command*);

    const Expression* makeExpression(const Command*);

    void math(const Command*);
    void jump(const Command*, u32_t&);

public:
    explicit Interpreter(const std::string&);
};

#endif //IKARUS_INTERPRETER_HPP
