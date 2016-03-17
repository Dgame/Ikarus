#include "Parser.hpp"
#include "Lexer.hpp"
#include "StringExpression.hpp"
#include "NumericExpression.hpp"
#include "util.hpp"

namespace Backend {
    OpCode* Parser::parseOpCode(Lexer& lexer) {
        const Token* tok = lexer.nextToken();

        switch (tok->getType()) {
            case Token::AMPERSAND:
                tok = lexer.nextToken();
                enforce(tok->getType() == Token::INTEGER, "Expected INTEGER as Variable-ID, got ", tok->getType());
                debug("VARIABLE ", tok->getInteger());

                return new OpCode(OpCode::VARIABLE, new NumericExpression(tok->getInteger()));
            case Token::TILDE:
                tok = lexer.nextToken();
                enforce(tok->getType() == Token::INTEGER, "Expected INTEGER as Offset, got ", tok->getType());
                debug("OFFSET ", tok->getInteger());

                return new OpCode(OpCode::OFFSET, new NumericExpression(tok->getInteger()));
            case Token::INTEGER:
                debug("VALUE (integer) ", tok->getInteger());

                return new OpCode(OpCode::VALUE, new NumericExpression(tok->getInteger()));
            case Token::DECIMAL:
                debug("VALUE (decimal) ", tok->getDecimal());

                return new OpCode(OpCode::VALUE, new NumericExpression(tok->getDecimal()));
            case Token::IDENTIFIER:
                debug("VALUE (identifier) ", tok->getIdentifier());

                return new OpCode(OpCode::VALUE, new StringExpression(tok->getIdentifier()));
            default:
                error("Unexpected Type ", tok->getType());

                return nullptr;
        }
    }

    void Parser::parseOperands(Instruction* instruction, Lexer& lexer) {
        while (true) {
            OpCode* opcode = this->parseOpCode(lexer);
            instruction->addOpCode(opcode);

            if (lexer.nextToken()->getType() != Token::COMMA) {
                break;
            }
        }
    }

    void Parser::parse(Lexer& lexer) {
        lexer.setIndex(0);

        while (true) {
            const Token* tok = lexer.getToken();
            if (tok->getType() == Token::NONE)
                break;

            enforce(tok->getType() == Token::IDENTIFIER, "Expected identifier");

            const Token* id = tok;
            debug("INSTRUCTION ", id->getIdentifier());

            Instruction* instruction = new Instruction(id->getIdentifier());

            switch (instruction->getType()) {
                case Instruction::LABEL:
                    if (lexer.nextToken()->getType() != Token::COLON)
                        error("Expected ':' after label");
                    else
                        lexer.nextToken();

                    _labels[id->getIdentifier()] = instruction->getId();
                    break;
                case Instruction::EXIT:
                case Instruction::RETURN:
                    lexer.nextToken();
                    break;
                default:
                    this->parseOperands(instruction, lexer);
            }

            _instructions.emplace_back(instruction);
        }
    }

    Parser::Parser(const char* pos, const char* const end) {
        debug("---- PARSER START ---");

        Lexer lexer(pos, end);
        this->parse(lexer);

        debug("---- PARSER FINISHED ---");
    }

    u32_t Parser::getIndexFor(const std::string& label) const {
        auto it = _labels.find(label);
        if (it != _labels.end()) {
            return it->second;
        }

        error("No address for Label ", label);

        return INT_MAX;
    }

    Instruction* Parser::getNext() {
        if (_index >= _instructions.size()) {
            return nullptr;
        }

        return _instructions.at(_index++).get();
    }
}