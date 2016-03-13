#include "Interpreter.hpp"
#include "Parser.hpp"
#include "OutputVisitor.hpp"
#include "RevelationVisitor.hpp"
#include "MathVisitor.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
#include "AddExpression.hpp"
#include "SubtractExpression.hpp"
#include "DecrementExpression.hpp"
#include "DivideExpression.hpp"
#include "MultiplyExpression.hpp"
#include "ModuloExpression.hpp"
#include "NotExpression.hpp"
#include "NegateExpression.hpp"
#include "IncrementExpression.hpp"
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
            case Instruction::ADD:
            case Instruction::SUB:
            case Instruction::DIV:
            case Instruction::MUL:
            case Instruction::MOD:
            case Instruction::INC:
            case Instruction::DEC:
            case Instruction::NEG:
            case Instruction::NOT:
                this->math(instruction);
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

            const u32_t index = rv.numeric->getAs<u32_t>();

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

u32_t Interpreter::getIndexOf(OpCode* opcode) {
    enforce(opcode->getType() == OpCode::VARIABLE, "Need a valid Variable as OpCode");

    RevelationVisitor rv;
    opcode->getExpression()->accept(rv);
    enforce(rv.numeric != nullptr, "Variable-ID must be numeric");

    return rv.numeric->getAs<u32_t>();
}

Expression* Interpreter::resolveVariable(OpCode* opcode) {
    const u32_t vi = this->getIndexOf(opcode);

    Expression* exp = this->fetchVariable(vi);
    enforce(exp != nullptr, "Invalid variable accessed @ ", vi);

    return exp;
}

template <typename T>
Expression* Interpreter::resolveOrMakeVariable(OpCode* opcode) {
    static_assert(std::is_base_of<Expression, T>::value, "That is not an Expression");
    static_assert(std::is_default_constructible<T>::value, "Cannot create Expression. No default CTor");

    const u32_t vi = this->getIndexOf(opcode);

    Expression* exp = this->fetchVariable(vi);
    if (!exp) {
        debug("No variable found, make new one");

        exp = new T();
        this->assignVariable(vi, exp);
    }

    return exp;
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

    const u32_t vi = this->getIndexOf(instruction->getOperand(0));
    debug("assign variable ", vi);

    Expression* exp = this->resolveExpression(instruction->getOperand(1));
    ::print(exp);

    this->assignVariable(vi, exp->clone());
}

void Interpreter::append(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "append need exactly two operands");

    Expression* exp = this->resolveOrMakeVariable<ArrayExpression>(instruction->getOperand(0));
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
    const u32_t index = rv.numeric->getAs<u32_t>();

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
    const u32_t index = rv.numeric->getAs<u32_t>();

    rv.reset();
    exp->accept(rv);

    enforce(rv.array != nullptr, "Need an array for fetch");

    this->pushStack(rv.array->fetch(index)->clone());
}

void Interpreter::pop(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "fetch need exactly one operands");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Can only pop into a variable");

    const u32_t vi = this->getIndexOf(instruction->getOperand(0));
    this->assignVariable(vi, this->popStack());
}

void Interpreter::push(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "fetch need exactly one operands");

    Expression* exp = this->resolveExpression(instruction->getOperand(0));
    this->pushStack(exp->clone());
}

Expression* Interpreter::makeExpression(Instruction* instruction) {
    switch (instruction->getType()) {
        case Instruction::ADD: {
            Expression* lhs = this->resolveExpression(instruction->getOperand(0));
            Expression* rhs = this->resolveExpression(instruction->getOperand(0));

            return new AddExpression(lhs, rhs);
        }
        case Instruction::SUB: {
            Expression* lhs = this->resolveExpression(instruction->getOperand(0));
            Expression* rhs = this->resolveExpression(instruction->getOperand(0));

            return new SubtractExpression(lhs, rhs);
        }
        case Instruction::MUL: {
            Expression* lhs = this->resolveExpression(instruction->getOperand(0));
            Expression* rhs = this->resolveExpression(instruction->getOperand(0));

            return new MultiplyExpression(lhs, rhs);
        }
        case Instruction::DIV: {
            Expression* lhs = this->resolveExpression(instruction->getOperand(0));
            Expression* rhs = this->resolveExpression(instruction->getOperand(0));

            return new DivideExpression(lhs, rhs);
        }
        case Instruction::MOD: {
            Expression* lhs = this->resolveExpression(instruction->getOperand(0));
            Expression* rhs = this->resolveExpression(instruction->getOperand(0));

            return new ModuloExpression(lhs, rhs);
        }
        case Instruction::NOT: {
            Expression* val = this->resolveExpression(instruction->getOperand(0));

            return new NotExpression(val);
        }
        case Instruction::NEG: {
            Expression* val = this->resolveExpression(instruction->getOperand(0));

            return new NegateExpression(val);
        }
        case Instruction::INC: {
            Expression* val = this->resolveExpression(instruction->getOperand(0));

            return new IncrementExpression(val);
        }
        case Instruction::DEC: {
            Expression* val = this->resolveExpression(instruction->getOperand(0));

            return new DecrementExpression(val);
        }
        default:
            error("Invalid math expression");
    }

    return nullptr;
}

void Interpreter::math(Instruction* instruction) {
    std::unique_ptr<Expression> exp(this->makeExpression(instruction));

    MathVisitor mv;
    exp->accept(mv);

    this->pushStack(new NumericExpression(mv.getValue()));
}