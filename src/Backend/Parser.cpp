#include "Backend/Parser.hpp"
#include "StringExpression.hpp"
#include "NumericExpression.hpp"

namespace Backend {
    OpCode* Parser::parseOpCode() {
        _lexer.next();
        auto tok = _lexer.getToken();

        switch (tok->getType()) {
            case Token::AMPERSAND:
                _lexer.next();

                tok = _lexer.getToken();
                enforce(tok->is(Token::INTEGER), "Expected INTEGER as Variable-ID, got ", tok->getType());
                debug("VARIABLE ", tok->getInteger());

                return new OpCode(OpCode::VARIABLE, new NumericExpression(tok->getInteger()));
            case Token::TILDE:
                _lexer.next();

                tok = _lexer.getToken();
                enforce(tok->is(Token::INTEGER), "Expected INTEGER as Offset, got ", tok->getType());
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

    void Parser::parseOperands(Instruction* instruction) {
        while (_lexer.getLocation().isValid()) {
            OpCode* opcode = this->parseOpCode();
            instruction->addOpCode(opcode);

            if (_lexer.next() != Token::COMMA) {
                break;
            }
        }
    }

    void Parser::parse() {
        while (_lexer.getLocation().isValid()) {
            auto tok = _lexer.getToken();
            if (tok->is(Token::NONE)) {
                break;
            }

            enforce(tok->is(Token::IDENTIFIER), "Expected identifier");

            auto id = tok->getIdentifier();
            debug("INSTRUCTION ", id);

            Instruction* instruction = new Instruction(id);

            switch (instruction->getType()) {
                case Instruction::LABEL:
                    enforce(_lexer.next() == Token::COLON, "Expected ':' after label");
                    _lexer.next();

                    _labels[id] = instruction->getId();
                    break;
                case Instruction::EXIT:
                case Instruction::RETURN:
                    _lexer.next();
                    break;
                default:
                    this->parseOperands(instruction);
            }

            _instructions.emplace_back(instruction);
        }
    }

    Parser::Parser(const char* pos, const char* const end) : _lexer(pos, end) {
        debug("---- PARSER START ---");

        this->parse();

        debug("---- PARSER FINISHED ---");
    }

    size_t Parser::getIndexFor(const std::string& label) const {
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