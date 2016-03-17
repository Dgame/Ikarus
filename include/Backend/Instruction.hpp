#ifndef IKARUS_INSTRUCTION_HPP
#define IKARUS_INSTRUCTION_HPP

#include <string>
#include <vector>
#include <memory>

#include "OpCode.hpp"
#include "types.hpp"

namespace Backend {
    class Instruction {
    public:
        static u32_t Amount;

        enum Type {
            NONE,
            ASSIGN,
            APPEND,
            SET_INDEX,
            EMPLACE,
            FETCH_DIM,
            FETCH,
            POP,
            PUSH,
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            PRINT,
            NOT,
            NEG,
            INC,
            DEC,
            IS_LOWER,
            IS_EQUAL,
            IS_LOWER_OR_EQUAL,
            LABEL,
            CALL,
            GOTO,
            GOTO_IF,
            GOTO_IF_NOT,
            EXIT,
            RETURN
        };

    private:
        std::vector<std::unique_ptr<OpCode>> _opcodes;

        Type _type = NONE;
        u32_t _id = 0;

        static Type DetermineType(const std::string&);

    public:
        explicit Instruction(const std::string&);

        explicit Instruction(Type);

        Type getType() const {
            return _type;
        }

        u32_t getId() const {
            return _id;
        }

        void addOpCode(OpCode*);

        OpCode* getOperand(u32_t index) {
            return _opcodes.at(index).get();
        }

        u32_t getOperandAmount() const {
            return _opcodes.size();
        }
    };
}

#endif //IKARUS_INSTRUCTION_HPP
