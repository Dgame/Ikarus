//
// Created by Randy on 05.03.2016.
//

#include <Command.hpp>
#include <util.hpp>
#include <map>

namespace {
    const std::map<std::string, Command::Type> String2Command = {
            {"assign", Command::ASSIGN},
            {"assign", Command::APPEND},
            {"index", Command::INDEX},
            {"fetch", Command::FETCH},
            {"push", Command::PUSH},
            {"pop", Command::POP},
            {"add", Command::ADD},
            {"sub", Command::SUB},
            {"mul", Command::MUL},
            {"div", Command::DIV},
            {"mod", Command::MOD},
            {"print", Command::PRINT},
            {"not", Command::NOT},
            {"neg", Command::NEG},
            {"inc", Command::INC},
            {"dec", Command::DEC},
            {"is_lower", Command::IS_LOWER},
            {"is_lower_or_equal", Command::IS_LOWER_OR_EQUAL},
            {"is_equal", Command::IS_EQUAL},
            {"jump", Command::JUMP},
            {"jump_if", Command::JUMP_IF},
            {"jump_if_not", Command::JUMP_IF_NOT},
            {"exit", Command::EXIT},
            {"return", Command::RETURN}
    };
}

u32_t Command::Amount = 0;

Command::Command(const std::string& token, const OpCode* lhs, const OpCode* rhs) : _left(lhs), _right(rhs) {
    _type = this->determineType(token);
    _id   = Command::Amount++;
}

Command::Command(const std::string& token, const OpCode* opc) : _left(opc) {
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
        case Command::JUMP_IF:
        case Command::JUMP_IF_NOT:
        case Command::JUMP:
            return _type;
        default:
            return Command::NONE;
    }
}
