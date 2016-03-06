//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_COMMAND_HPP
#define IKARUS_COMMAND_HPP

#include <string>
#include <memory>
#include <OpCode.hpp>
#include <types.hpp>

namespace ik {
    class Command {
    public:
        static u32_t Amount;

        enum Type {
            NONE,
            ASSIGN,
            APPEND,
            POP,
            PUSH,
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            PRINT,
            GOTO,
            CONCAT,
            NOT,
            NEG,
            INC,
            DEC,
            SKIP_IF_EQUAL,
            JUMP_IF_NOT_EQUAL,
            JUMP_IF_GREATER,
            JUMP_IF_LOWER,
            JUMP_IF_LOWER_OR_EQUAL,
            JUMP_IF_GREATER_OR_EQUAL
        };

    private:
        std::unique_ptr<OpCode> _left;
        std::unique_ptr<OpCode> _right;

        Type  _type;
        u32_t _id = 0;

        Type determineType(const std::string&) const;

    public:
        explicit Command(const std::string&, OpCode*, OpCode*);

        explicit Command(const std::string&, OpCode*);

        Type getType() const {
            return _type;
        }

        u32_t getId() const {
            return _id;
        }

        const OpCode* getLeft() const {
            return _left.get();
        }

        const OpCode* getRight() const {
            return _right.get();
        }

        Type isJump() const;
    };
}

#endif //IKARUS_COMMAND_HPP
