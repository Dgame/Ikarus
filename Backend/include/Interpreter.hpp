//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_INTERPRETER_HPP
#define IKARUS_INTERPRETER_HPP

#include <string>
#include <vector>
#include <memory>
#include "Command.hpp"
#include "Value/Value.hpp"

namespace ik {
    class OpCode;

    class Interpreter {
    private:
        std::vector<std::unique_ptr<Value>> _variables;
        std::vector<std::unique_ptr<Value>> _stack;

        int _stack_offset = 0;

        const Value* getValue(const OpCode*) const;

        void interpret(const std::vector<std::unique_ptr<Command>>&);

        void assign(const Command*);

        void push(const Command*);

        void print(const Command*);

        void add(const Command*);

    public:
        explicit Interpreter(const std::string&);
    };
}

#endif //IKARUS_INTERPRETER_HPP
