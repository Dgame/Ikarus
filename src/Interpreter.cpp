#include "Interpreter.hpp"
#include "Parser.hpp"
#include "OutputVisitor.hpp"
#include "RevelationVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
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
                debug("APPEND");

                this->append(instruction);
                break;
            case Instruction::INDEX:
                debug("INDEX");

                this->index(instruction);
                break;
            case Instruction::FETCH:
                debug("FETCH");

                this->fetch(instruction);
                break;
            case Instruction::POP:
                this->pop(instruction);
                break;
            case Instruction::PUSH:
                this->push(instruction);
                break;
        }
    }

    return true;
}

Expression* Interpreter::resolveExpression(OpCode* opcode) {
    switch (opcode->getType()) {
        case OpCode::VARIABLE:
        case OpCode::OFFSET: {
            RevelationVisitor rv;
            opcode->getExpression()->accept(rv);
            enforce(rv.numeric != nullptr, "Variable-ID must be numeric");

            const u32_t index = static_cast<u32_t>(rv.numeric->getNumber());

            if (opcode->getType() == OpCode::VARIABLE)
                return this->fetchVariable(index);

            return this->fetchStack(index);
        }
        case OpCode::VALUE:
            return opcode->getExpression();
    }

    error("Unexpected OpCode");

    return nullptr;
}

Expression* Interpreter::resolveVariable(OpCode* opcode, u32_t* index) {
    enforce(opcode->getType() == OpCode::VARIABLE, "Need a valid Variable as OpCode");

    RevelationVisitor rv;
    opcode->getExpression()->accept(rv);
    enforce(rv.numeric != nullptr, "Variable-ID must be numeric");

    const u32_t vi = static_cast<u32_t>(rv.numeric->getNumber());
    if (index != nullptr) {
        *index = vi;
    }

    return this->fetchVariable(vi);
}

void Interpreter::print(Instruction* instruction) {
    for (u32_t i = 0; i < instruction->getOperandAmount(); i++) {
        Expression* exp = this->resolveExpression(instruction->getOperand(i));
        ::print(exp);
    }

    std::cout << std::endl;
}

void Interpreter::assign(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "assign need exactly two operands");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Expected a variable");

    u32_t vi;
    this->resolveVariable(instruction->getOperand(0), &vi);
    debug("assign variable ", vi);

    Expression* exp = this->resolveExpression(instruction->getOperand(1));
    ::print(exp);

    this->assignVariable(vi, exp->clone());
}

void Interpreter::append(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "append need exactly two operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));
    Expression* val = this->resolveExpression(instruction->getOperand(1));
    ::print(val);

    RevelationVisitor rv;
    exp->accept(rv);

    enforce(rv.array != nullptr, "Cann only append on an array");

    rv.array->assign(val->clone());
}

void Interpreter::index(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "index need exactly two operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));
    Expression* idx = this->resolveExpression(instruction->getOperand(1));

    RevelationVisitor rv;
    idx->accept(rv);

    enforce(rv.numeric != nullptr, "Index must be numeric");
    const u32_t index = static_cast<u32_t>(rv.numeric->getNumber());

    rv.reset();
    exp->accept(rv);

    enforce(rv.array != nullptr, "Need an array for index");

    rv.array->setIndex(index);
}

void Interpreter::fetch(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "fetch need exactly two operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));
    Expression* idx = this->resolveExpression(instruction->getOperand(1));

    RevelationVisitor rv;
    idx->accept(rv);

    enforce(rv.numeric != nullptr, "Fetch-Index must be numeric");
    const u32_t index = static_cast<u32_t>(rv.numeric->getNumber());

    rv.reset();
    exp->accept(rv);

    enforce(rv.array != nullptr, "Need an array for fetch");

    this->pushStack(rv.array->fetch(index)->clone());
}

void Interpreter::pop(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "fetch need exactly one operands");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Can only pop into a variable");

    u32_t vi;
    this->resolveVariable(instruction->getOperand(0), &vi);
    this->assignVariable(vi, this->popStack());
}

void Interpreter::push(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "fetch need exactly one operands");

    Expression* exp = this->resolveExpression(instruction->getOperand(0));
    this->pushStack(exp->clone());
}