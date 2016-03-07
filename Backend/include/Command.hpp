//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_COMMAND_HPP
#define IKARUS_COMMAND_HPP

#include <string>
#include <memory>
#include <OpCode.hpp>
#include <types.hpp>

class Command {
public:
    static u32_t Amount;

    enum Type {
        NONE,
        ASSIGN,
        APPEND,
        INDEX,
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
        IS_LOWER_OR_EQUAL,
        IS_EQUAL,
        JUMP,
        JUMP_IF,
        JUMP_IF_NOT,
        EXIT,
        RETURN
    };

private:
    std::unique_ptr<const OpCode> _left;
    std::unique_ptr<const OpCode> _right;

    Type  _type;
    u32_t _id = 0;

    Type determineType(const std::string&) const;

public:
    explicit Command(const std::string&, const OpCode*, const OpCode*);

    explicit Command(const std::string&, const OpCode*);

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

#endif //IKARUS_COMMAND_HPP
