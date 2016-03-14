#include "Instruction.hpp"
#include "util.hpp"
#include <map>

namespace {
    const std::map<std::string, Instruction::Type> Instructions = {
            {"assign", Instruction::ASSIGN},
            {"append", Instruction::APPEND},
            {"set_index", Instruction::SET_INDEX},
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
            {"goto", Instruction::GOTO},
            {"goto_if", Instruction::GOTO_IF},
            {"goto_if_not", Instruction::GOTO_IF_NOT},
            {"exit", Instruction::EXIT},
            {"return", Instruction::RETURN}
    };
}

u32_t Instruction::Amount = 0;

Instruction::Type Instruction::DetermineType(const std::string& id) {
    auto it = Instructions.find(id);
    if (it != Instructions.end()) {
        return it->second;
    }

    return Instruction::LABEL;
}

Instruction::Instruction(const std::string& id) : Instruction(DetermineType(id)) { }

Instruction::Instruction(Type type) : _type(type), _id(Amount++) { }

void Instruction::addOpCode(OpCode* opcode) {
    _opcodes.emplace_back(opcode);
}