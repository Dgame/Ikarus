//
// Created by Randy on 05.03.2016.
//

#ifndef IKARUS_LEXER_HPP
#define IKARUS_LEXER_HPP

#include <string>
#include <vector>
#include "OpCode.hpp"
#include "Command.hpp"

namespace ik {
    class Lexer {
    private:
        std::vector<std::unique_ptr<Command>> _commands;
        const char* _ptr = nullptr;

        void skipSpaces();

        bool accept(char);

        std::string parseString();

        int parseNumber();

        Value* parseValue();

        OpCode* parseOpCode();

    public:
        explicit Lexer(const std::string&);

        const std::vector<std::unique_ptr<Command>>& getCommands() const {
            return _commands;
        }
    };
}


#endif //IKARUS_LEXER_HPP
