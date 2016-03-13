#ifndef IKARUS_PARSER_HPP
#define IKARUS_PARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include "Instruction.hpp"

class Lexer;
class Declaration;
class Token;

class Parser {
private:
    u32_t _index = 0;

    OpCode* parseOpCode(Lexer&);
    void parse(Lexer&);

    std::vector<std::unique_ptr<Instruction>> _instructions;

public:
    explicit Parser(const std::string&);

    void setIndex(u32_t index) {
        _index = 0;
    }

    u32_t getIndex() const {
        return _index;
    }

    Instruction* getNext() {
        if (_index >= _instructions.size()) {
            return nullptr;
        }

        return _instructions.at(_index++).get();
    }
};

#endif //IKARUS_PARSER_HPP
