#ifndef IKARUS_INTERPRETER_HPP
#define IKARUS_INTERPRETER_HPP

#include <string>
#include <vector>
#include <memory>

#include "types.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

namespace Backend {
    class Parser;

    class Interpreter {
    private:
        std::vector<std::unique_ptr<Expression>> _variables;
        std::vector<std::unique_ptr<Expression>> _stack;

        size_t _stack_offset = 0;
        size_t _backtrack = 0;

        void assignVariable(size_t, Expression*);

        void pushStack(Expression*);

        std::unique_ptr<Expression> popStack();

        Expression* fetchStack(size_t);

        Expression* fetchVariable(size_t);

        bool interpret(Parser&);

        Expression* resolveExpression(OpCode*);

        size_t getIndexOf(OpCode*);

        Expression* resolveVariable(OpCode*);

        void print(Instruction*);

        void assign(Instruction*);

        void append(Instruction*);

        void setIndex(Instruction*);

        void emplace(Instruction*);

        void fetchDim(Instruction*);

        void fetch(Instruction*);

        void pop(Instruction*);

        void push(Instruction*);

        bool isLower(Instruction*);

        bool isEqual(Instruction*);

        bool isNotEqual(Instruction*);

        bool isLowerOrEqual(Instruction*);

        void call(Instruction*, Parser&);

        void goTo(Instruction*, Parser&);

        void goToIf(Instruction*, Parser&);

        void goToIfNot(Instruction*, Parser&);

        void math(Instruction*);

        Expression* makeExpression(Instruction*);

    public:
        explicit Interpreter(const char*, const char* const);
    };
}

#endif //IKARUS_INTERPRETER_HPP
