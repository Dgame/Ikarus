#include "Interpreter.hpp"
#include "Parser.hpp"
#include "OutputVisitor.hpp"
#include "RevelationVisitor.hpp"
#include "MathVisitor.hpp"
#include "NumericExpression.hpp"
#include "StringExpression.hpp"
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

#include <cmath>
#include <limits>

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

std::unique_ptr<Expression> Interpreter::popStack() {
    enforce(_stack_offset > 0, "Invalid Stack-Offset");

    _stack_offset--;

    return std::move(_stack.at(_stack_offset));
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

bool Interpreter::interpret(Parser& parser) {
    for (Instruction* instruction = parser.getNext(); instruction != nullptr; instruction = parser.getNext()) {
        switch (instruction->getType()) {
            case Instruction::EXIT:
                debug("EXIT");
                enforce(instruction->getOperandAmount() == 0, "exit need no operands");
                return true;
            case Instruction::RETURN:
                debug("RETURN");
                enforce(instruction->getOperandAmount() == 0, "return need no operands");
                parser.setIndex(_backtrack);
                break;
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
            case Instruction::SET_INDEX:
                debug("SET_INDEX");
                this->setIndex(instruction);
                break;
            case Instruction::EMPLACE:
                debug("EMPLACE");
                this->emplace(instruction);
                break;
            case Instruction::FETCH_DIM:
                debug("FETCH_DIM");
                this->fetchDim(instruction);
                break;
            case Instruction::FETCH:
                debug("FETCH");
                this->fetch(instruction);
                break;
            case Instruction::POP:
                debug("POP");
                this->pop(instruction);
                break;
            case Instruction::PUSH:
                debug("PUSH");
                this->push(instruction);
                break;
            case Instruction::IS_LOWER:
                debug("IS_LOWER");
                this->isLower(instruction);
                break;
            case Instruction::IS_EQUAL:
                debug("IS_EQUAL");
                this->isEqual(instruction);
                break;
            case Instruction::IS_LOWER_OR_EQUAL:
                debug("IS_LOWER_OR_EQUAL");
                this->isLowerOrEqual(instruction);
                break;
            case Instruction::GOTO:
                debug("GOTO");
                this->goTo(instruction, parser);
                break;
            case Instruction::GOTO_IF:
                debug("GOTO_IF");
                this->goToIf(instruction, parser);
                break;
            case Instruction::GOTO_IF_NOT:
                debug("GOTO_IF_NOT");
                this->goToIfNot(instruction, parser);
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
                debug("MATH");
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
            RevelationVisitor<NumericExpression> rnv;
            opcode->getExpression()->accept(rnv);
            enforce(rnv.isValid(), "Variable-ID must be numeric");

            const u32_t index = rnv.getExpression()->getAs<u32_t>();
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

    RevelationVisitor<NumericExpression> rnv;
    opcode->getExpression()->accept(rnv);
    enforce(rnv.isValid(), "Variable-ID must be numeric");

    return rnv.getExpression()->getAs<u32_t>();
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
        debug("No variable found, make a new one");

        exp = new T();
        this->assignVariable(vi, exp);
    }

    return exp;
}

void Interpreter::print(Instruction* instruction) {
    OutputVisitor ov(std::cout);

    for (u32_t i = 0; i < instruction->getOperandAmount(); i++) {
        Expression* exp = this->resolveExpression(instruction->getOperand(i));
        exp->accept(ov);
    }

    std::cout << std::endl;
}

void Interpreter::assign(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "assign need exactly two operands");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Expected a variable");

    const u32_t vi = this->getIndexOf(instruction->getOperand(0));
    debug("assign variable ", vi);

    Expression* exp = this->resolveExpression(instruction->getOperand(1));
#if DEBUG
    ::print(exp);
#endif
    this->assignVariable(vi, exp->clone());
}

void Interpreter::append(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "append need exactly two operands");

    Expression* exp = this->resolveOrMakeVariable<ArrayExpression>(instruction->getOperand(0));
    Expression* val = this->resolveExpression(instruction->getOperand(1));
#if DEBUG
    ::print(val);
#endif
    RevelationVisitor<ArrayExpression> rav;
    exp->accept(rav);

    enforce(rav.isValid(), "Cann only append on an array");

    rav.getExpression()->append(val->clone());
}

void Interpreter::setIndex(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "set_index need exactly one operand");

    Expression* exp = this->resolveExpression(instruction->getOperand(0));

    RevelationVisitor<NumericExpression> rnv;
    exp->accept(rnv);

    enforce(rnv.isValid(), "Index must be integer");

    this->pushStack(exp->clone());
}

void Interpreter::emplace(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "emplace need exactly two operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));
    Expression* val = this->resolveExpression(instruction->getOperand(1));
    auto idx = this->popStack();

    RevelationVisitor<NumericExpression> rnv;
    idx->accept(rnv);

    enforce(rnv.isValid(), "Index must be numeric");

    const u32_t index = rnv.getExpression()->getAs<u32_t>();

    RevelationVisitor<ArrayExpression> rav;
    exp->accept(rav);

    enforce(rav.isValid(), "Need an array for emplace");

    rav.getExpression()->emplace(index, val->clone());
}

void Interpreter::fetchDim(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "fetch_dim need exactly one operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));

    RevelationVisitor<ArrayExpression> rav;
    exp->accept(rav);

    enforce(rav.isValid(), "Can only fetch dimension of an array");

    this->pushStack(new NumericExpression(rav.getExpression()->getAmount()));
}

void Interpreter::fetch(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "fetch need exactly two operands");

    Expression* exp = this->resolveVariable(instruction->getOperand(0));
    Expression* idx = this->resolveExpression(instruction->getOperand(1));

    RevelationVisitor<NumericExpression> rnv;
    idx->accept(rnv);

    enforce(rnv.isValid(), "Fetch-Index must be numeric");
    const u32_t index = rnv.getExpression()->getAs<u32_t>();

    RevelationVisitor<ArrayExpression> rav;
    exp->accept(rav);

    enforce(rav.isValid(), "Need an array for fetch");

    this->pushStack(rav.getExpression()->fetch(index)->clone());
}

void Interpreter::pop(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "pop need exactly one operand");
    enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Can only pop into a variable");

    auto val = this->popStack();

    const u32_t vi = this->getIndexOf(instruction->getOperand(0));
    this->assignVariable(vi, val.release());
}

void Interpreter::push(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 1, "push need exactly one operand");

    Expression* exp = this->resolveExpression(instruction->getOperand(0));
    this->pushStack(exp->clone());
}

bool Interpreter::isLower(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "is_lower need exactly two operands");

    Expression* lhs = this->resolveExpression(instruction->getOperand(0));
    Expression* rhs = this->resolveExpression(instruction->getOperand(1));

    RevelationVisitor<NumericExpression> rnv_lhs;
    lhs->accept(rnv_lhs);

    enforce(rnv_lhs.isValid(), "Invalid left hand side expression");

    RevelationVisitor<NumericExpression> rnv_rhs;
    rhs->accept(rnv_rhs);

    enforce(rnv_rhs.isValid(), "Invalid right hand side expression");

    const f32_t lhs_num = rnv_lhs.getExpression()->getNumber();
    const f32_t rhs_num = rnv_rhs.getExpression()->getNumber();

    const i32_t result = lhs_num < rhs_num;
    this->pushStack(new NumericExpression(result));

    return result != 0;
}

bool Interpreter::isEqual(Instruction* instruction) {
    enforce(instruction->getOperandAmount() == 2, "is_lower need exactly two operands");

    Expression* lhs = this->resolveExpression(instruction->getOperand(0));
    Expression* rhs = this->resolveExpression(instruction->getOperand(1));

    RevelationVisitor<NumericExpression> rnv_lhs;
    lhs->accept(rnv_lhs);

    enforce(rnv_lhs.isValid(), "Invalid left hand side expression");

    RevelationVisitor<NumericExpression> rnv_rhs;
    rhs->accept(rnv_rhs);

    enforce(rnv_rhs.isValid(), "Invalid right hand side expression");

    const f32_t lhs_num = rnv_lhs.getExpression()->getNumber();
    const f32_t rhs_num = rnv_rhs.getExpression()->getNumber();

    const i32_t result = std::fabs(lhs_num - rhs_num) < std::numeric_limits<f32_t>::epsilon();
    this->pushStack(new NumericExpression(result));

    return result != 0;
}

bool Interpreter::isLowerOrEqual(Instruction* instruction) {
    if (this->isLower(instruction)) {
        return true;
    }

    return this->isEqual(instruction);
}

void Interpreter::goTo(Instruction* instruction, Parser& parser) {
    enforce(instruction->getOperandAmount() == 1, "goto need exactly one operand");

    Expression* exp = this->resolveExpression(instruction->getOperand(0));

    RevelationVisitor<StringExpression> rsv;
    exp->accept(rsv);

    enforce(rsv.isValid(), "goto need's a string label");

    const u32_t index = parser.getIndexFor(rsv.getExpression()->getValue());
    _backtrack = parser.getIndex();

    debug("goto ", index, " from ", _backtrack);

    parser.setIndex(index);
}

void Interpreter::goToIf(Instruction* instruction, Parser& parser) {
    auto val = this->popStack();

    RevelationVisitor<NumericExpression> rnv;
    val->accept(rnv);

    enforce(rnv.isValid(), "Expected a numeric condition");

    if (rnv.getExpression()->getAs<i32_t>() != 0)
        this->goTo(instruction, parser);
}

void Interpreter::goToIfNot(Instruction* instruction, Parser& parser) {
    auto val = this->popStack();

    RevelationVisitor<NumericExpression> rnv;
    val->accept(rnv);

    enforce(rnv.isValid(), "Expected a numeric condition");

    if (rnv.getExpression()->getAs<i32_t>() == 0)
        this->goTo(instruction, parser);
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