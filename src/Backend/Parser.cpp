#include "Parser.hpp"
#include "Lexer.hpp"
#include "NumericExpression.hpp"
#include "util.hpp"

Parser::Parser(const std::string& str) {
    debug("---- PARSER START ---");

    Lexer lex(str);

    this->parse(lex);

    debug("---- PARSER FINISHED ---");
}

OpCode* Parser::parseOpCode(Lexer& lex) {
    const Token* tok = lex.getNext();

    if (tok->getType() == Token::IDENTIFIER) {
        return nullptr;
    }

    switch (tok->getType()) {
        case Token::AMPERSAND:
            tok = lex.getNext();
            enforce(tok->getType() == Token::INTEGER, "Expected INTEGER as Variable-ID, got ", tok->getType());

            debug("VARIABLE ", tok->getInteger());

            return new OpCode(OpCode::VARIABLE, new NumericExpression(tok->getInteger()));
        case Token::TILDE:
            tok = lex.getNext();
            enforce(tok->getType() == Token::INTEGER, "Expected INTEGER as Offset, got ", tok->getType());

            debug("OFFSET ", tok->getInteger());

            return new OpCode(OpCode::OFFSET, new NumericExpression(tok->getInteger()));
        case Token::INTEGER:
            debug("VALUE ", tok->getInteger());

            return new OpCode(OpCode::VALUE, new NumericExpression(tok->getInteger()));
        case Token::DECIMAL:
            debug("VALUE ", tok->getDecimal());

            return new OpCode(OpCode::VALUE, new NumericExpression(tok->getDecimal()));
        default:
            error("Unexpected Type ", tok->getType());

            return nullptr;
    }
}

void Parser::parse(Lexer& lex) {
    lex.setIndex(0);

    for (const Token* tok = lex.getNext(); tok->getType() != Token::NONE;) {
        enforce(tok->getType() == Token::IDENTIFIER, "Expected identifier");

        debug("INSTRUCTION ", tok->getIdentifier());

        Instruction* instruction = new Instruction(tok->getIdentifier());

        OpCode* opcode = this->parseOpCode(lex);
        while (opcode != nullptr) {
            instruction->addOpCode(opcode);

            tok = lex.getNext();
            if (tok->getType() != Token::COMMA)
                break;

            opcode = this->parseOpCode(lex);
        }

        _instructions.emplace_back(instruction);
    }
}