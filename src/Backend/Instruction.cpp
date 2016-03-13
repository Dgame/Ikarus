#include "Instruction.hpp"
#include "util.hpp"
#include <map>

namespace {
    const std::map<std::string, Instruction::Type> Instructions = {
            {"assign", Instruction::ASSIGN},
            {"append", Instruction::APPEND},
            {"emplace", Instruction::EMPLACE},
            {"fetch_dim", Instruction::FETCH_DIM},
            {"fetch", Instruction::FETCH},
            {"push", Instruction::PUSH},
            {"pop", Instruction::POP},
            {"add", Instruction::ADD},
            {"sub", Instruction::SUB},
            {"mul", Instruction::MUL},
            {"div", Instruction::DIV},
            {"mod", Instruction::MOD},
            {"print", Instruction::PRINT},
            {"not", Instruction::NOT},
            {"neg", Instruction::NEG},
            {"inc", Instruction::INC},
            {"dec", Instruction::DEC},
            {"is_lower", Instruction::IS_LOWER},
            {"is_lower_or_equal", Instruction::IS_LOWER_OR_EQUAL},
            {"is_equal", Instruction::IS_EQUAL},
            {"jump", Instruction::JUMP},
            {"jump_if", Instruction::JUMP_IF},
            {"jump_if_not", Instruction::JUMP_IF_NOT},
            {"exit", Instruction::EXIT},
            {"return", Instruction::RETURN}
    };
}

u32_t Instruction::Amount = 0;

Instruction::Type Instruction::DetermineType(const std::string& str) {
    auto it = Instructions.find(str);
    if (it != Instructions.end()) {
        return it->second;
    }

    error("No type for: ", str);

    return Instruction::NONE;
}

Instruction::Instruction(const std::string& str) : _id(Amount++) {
    _type = DetermineType(str);
}

void Instruction::addOpCode(OpCode* opcode) {
    _opcodes.emplace_back(opcode);
}