#ifndef IKARUS_PARSER_HPP
#define IKARUS_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "Instruction.hpp"

class Token;

namespace Backend {
    class Lexer;

    class Parser {
    private:
        u32_t _index = 0;

        OpCode *parseOpCode(Lexer &);

        void parseOperands(Instruction *, Lexer &);

        void parse(Lexer &);

        std::vector<std::unique_ptr<Instruction>> _instructions;
        std::map<std::string, u32_t> _labels;

    public:
        explicit Parser(const char *, const char *const);

        void setIndex(u32_t index) {
            _index = index;
        }

        u32_t getIndex() const {
            return _index;
        }

        u32_t getIndexFor(const std::string &) const;

        Instruction *getNext();
    };
}

#endif //IKARUS_PARSER_HPP
