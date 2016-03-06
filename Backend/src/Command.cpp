//
// Created by Randy on 05.03.2016.
//

#include <Command.hpp>
#include <util.hpp>
#include <map>

namespace {
    using ik::Command;

    const std::map<std::string, Command::Type> String2Command = {
            {"assign", Command::ASSIGN},
            {"append", Command::APPEND},
            {"push",   Command::PUSH},
            {"pop",    Command::POP},
            {"add",    Command::ADD},
            {"sub",    Command::SUB},
            {"mul",    Command::MUL},
            {"div",    Command::DIV},
            {"mod",    Command::MOD},
            {"print",  Command::PRINT},
            {"goto",   Command::GOTO},
            {"concat", Command::CONCAT},
            {"not",    Command::NOT},
            {"neg",    Command::NEG},
            {"inc",    Command::INC},
            {"dec",    Command::DEC},
            {"je",     Command::JUMP_IF_EQUAL},
            {"jne",    Command::JUMP_IF_NOT_EQUAL},
            {"jg",     Command::JUMP_IF_GREATER},
            {"jl",     Command::JUMP_IF_LOWER},
            {"jle",    Command::JUMP_IF_LOWER_OR_EQUAL},
            {"jge",    Command::JUMP_IF_GREATER_OR_EQUAL},
    };

    const std::map<Command::Type, std::string> Command2String = {
            {Command::ASSIGN,                   "assign"},
            {Command::APPEND,                   "append"},
            {Command::PUSH,                     "push"},
            {Command::POP,                      "pop"},
            {Command::ADD,                      "add"},
            {Command::SUB,                      "sub"},
            {Command::MUL,                      "mul"},
            {Command::DIV,                      "div"},
            {Command::MOD,                      "mod"},
            {Command::PRINT,                    "print"},
            {Command::GOTO,                     "goto"},
            {Command::CONCAT,                   "concat",},
            {Command::NOT,                      "not"},
            {Command::NEG,                      "neg"},
            {Command::INC,                      "inc"},
            {Command::DEC,                      "dec"},
            {Command::JUMP_IF_EQUAL,            "je"},
            {Command::JUMP_IF_NOT_EQUAL,        "jne"},
            {Command::JUMP_IF_GREATER,          "jg"},
            {Command::JUMP_IF_LOWER,            "jl"},
            {Command::JUMP_IF_LOWER_OR_EQUAL,   "jle"},
            {Command::JUMP_IF_GREATER_OR_EQUAL, "jge"},
    };
}

namespace ik {
    u32_t Command::Amount = 0;

    Command::Command(const std::string& token, OpCode* lhs, OpCode* rhs) : _left(lhs), _right(rhs) {
        _type = this->determineType(token);
        _id   = Command::Amount++;
    }

    Command::Command(const std::string& token, OpCode* opc) : _left(opc) {
        _type = this->determineType(token);
        _id   = Command::Amount++;
    }

    Command::Type Command::determineType(const std::string& token) const {
        auto it = String2Command.find(token);
        if (it != String2Command.end()) {
            return it->second;
        }

        error("No type for: ", token);

        return Command::NONE;
    }

    Command::Type Command::isJump() const {
        switch (_type) {
            case Command::JUMP_IF_EQUAL:
            case Command::JUMP_IF_NOT_EQUAL:
            case Command::JUMP_IF_GREATER:
            case Command::JUMP_IF_LOWER:
            case Command::JUMP_IF_LOWER_OR_EQUAL:
            case Command::JUMP_IF_GREATER_OR_EQUAL:
            case Command::GOTO:
                return _type;
            default:
                return Command::NONE;
        }
    }
}