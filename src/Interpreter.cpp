#include "Interpreter.hpp"
#include "Parser.hpp"
#include "OutputVisitor.hpp"
#include "NumericExpression.hpp"
#include "util.hpp"

Interpreter::Interpreter(const std::string& str) : _variables(8), _stack(8) {
    debug("---- INTERPRETER START ----");

    Parser p(str);

    this->interpret(p);

    debug("---- INTERPRETER FINISHED ----");
}

void Interpreter::assignVariable(u32_t index, Expression* exp) {
    if (index >= _variables.size()) {
        _variables.resize(index * 2);
    }

    _variables.at(index).reset(exp);
}

void Interpreter::pushStack(Expression* exp) {
    if (_stack_offset >= _stack.size()) {
        _stack.resize(_stack_offset * 2);
    }

    _stack.at(_stack_offset).reset(exp);
    _stack_offset++;
}

Expression* Interpreter::popStack() {
    _stack_offset--;

    return _stack.at(_stack_offset).release();
}

Expression* Interpreter::fetchStack(u32_t index) {
    enforce(_stack.size() >= index, "Invalid offset index: ", index);
    debug("<OFFSET ", index, ">");

    return _stack.at(index).get();
}

Expression* Interpreter::fetchVariable(u32_t index) {
    enforce(_variables.size() >= index, "Invalid variable index: ", index);
    debug("<VARIABLE ", index, ">");

    return _variables.at(index).get();
}

bool Interpreter::interpret(Parser& p) {
    for (Instruction* instruction = p.getNext(); instruction != nullptr; instruction = p.getNext()) {
        switch (instruction->getType()) {
            case Instruction::EXIT:
                debug("EXIT");

                return true;
            case Instruction::PRINT:
                debug("PRINT");

                this->print(instruction);
                break;
            case Instruction::ASSIGN:
                debug("ASSIGN");

                this->assign(instruction);
                break;
            case Instruction::APPEND:

                break;
        }
    }

    return true;
}

Expression* Interpreter::resolve(OpCode* opcode) {
    switch (opcode->getType()) {
        case OpCode::VARIABLE: {
            const NumericExpression* ne = opcode->getExpression()->isNumeric();
            enforce(ne != nullptr, "Variable-ID must be numeric");

            const u32_t index = static_cast<u32_t>(ne->getNumber());

            return this->fetchVariable(index);
        }
        case OpCode::OFFSET: {
            const NumericExpression* ne = opcode->getExpression()->isNumeric();
            enforce(ne != nullptr, "Offset must be numeric");

            const u32_t index = static_cast<u32_t>(ne->getNumber());

            return this->fetchStack(index);
        }
        case OpCode::VALUE:
            return opcode->getExpression();
    }

    error("Unexpected OpCode");

    return nullptr;
}

void Interpreter::print(Instruction* instruction) {
    for (u32_t i = 0; i < instruction->getOperandAmount(); i++) {
        Expression* exp = this->resolve(instruction->getOperand(i));
        ::print(exp);
    }

    std::cout << std::endl;
}

void Interpreter::assign(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "assign need exactly two operands");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Expected a variable");

    const NumericExpression* ne = instruction->getOperand(0)->getExpression()->isNumeric();
    enforce(ne != nullptr, "Variable-ID must be numeric");

    const u32_t index = static_cast<u32_t>(ne->getNumber());

    debug("assign variable ", index);

    Expression* exp = this->resolve(instruction->getOperand(1));
    ::print(exp);

    this->assignVariable(index, exp->clone());
}

void Interpreter::append(Instruction*) {

}