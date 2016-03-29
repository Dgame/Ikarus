#include "Backend/Interpreter.hpp"
#include "Backend/Parser.hpp"
#include "OutputVisitor.hpp"
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

#include <cmath>
#include <limits>

namespace Backend {
    Interpreter::Interpreter(const char* pos, const char* const end) : _variables(8), _stack(8) {
        debug("---- INTERPRETER START ----");

        Parser parser(pos, end);
        this->interpret(parser);

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
        for (Instruction* instruction = parser.getNext(); is(instruction); instruction = parser.getNext()) {
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
                case Instruction::IS_NOT_EQUAL:
                    debug("IS_NOT_EQUAL");
                    this->isNotEqual(instruction);
                    break;
                case Instruction::IS_LOWER_OR_EQUAL:
                    debug("IS_LOWER_OR_EQUAL");
                    this->isLowerOrEqual(instruction);
                    break;
                case Instruction::CALL:
                    debug("CALL");
                    this->call(instruction, parser);
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
                case Instruction::NONE:
                    error("Unexpected Instruction");
                case Instruction::LABEL:
                    break;
            }
        }

        return true;
    }

    Expression* Interpreter::resolveExpression(OpCode* opcode) {
        switch (opcode->getType()) {
            case OpCode::VARIABLE:
            case OpCode::OFFSET: {
                const size_t index = this->getIndexOf(opcode);
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
        enforce(opcode->getType() == OpCode::VARIABLE || opcode->getType() == OpCode::OFFSET, "Need a valid Variable or Offset as OpCode");

        return opcode->getExpression()->is<NumericExpression>().ensure("ID must be numeric")->getAs<u32_t>();
    }

    Expression* Interpreter::resolveVariable(OpCode* opcode) {
        enforce(opcode->getType() == OpCode::VARIABLE, "Need a valid Variable as OpCode");

        const size_t vi = this->getIndexOf(opcode);
        Expression* exp = this->fetchVariable(vi);
        enforce(is(exp), "Invalid variable accessed @ ", vi);

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

        const size_t vi = this->getIndexOf(instruction->getOperand(0));
        debug("assign variable ", vi);
        Expression* exp = this->resolveExpression(instruction->getOperand(1));
#if DEBUG
        ::print(exp);
#endif
        this->assignVariable(vi, exp->clone());
    }

    void Interpreter::append(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 2, "append need exactly two operands");

        const size_t vi = this->getIndexOf(instruction->getOperand(0));
        Expression* exp = this->fetchVariable(vi);
        if (!exp) {
            debug("No variable found, gen a new one");
            exp = new ArrayExpression();
            this->assignVariable(vi, exp);
        }

        Expression* val = this->resolveExpression(instruction->getOperand(1));
#if DEBUG
        ::print(val);
#endif
        exp->is<ArrayExpression>().ensure("Can only append on an array")->append(val->clone());
    }

    void Interpreter::setIndex(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 1, "set_index need exactly one operand");

        Expression* exp = this->resolveExpression(instruction->getOperand(0));
        exp->is<NumericExpression>().ensure("Index must be integer");

        this->pushStack(exp->clone());
    }

    void Interpreter::emplace(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 2, "emplace need exactly two operands");

        Expression* exp = this->resolveVariable(instruction->getOperand(0));
        Expression* val = this->resolveExpression(instruction->getOperand(1));

        auto idx = this->popStack();
        const u32_t index = idx->is<NumericExpression>().ensure("Index must be numeric")->getAs<u32_t>();

        exp->is<ArrayExpression>().ensure("Need an array for emplace")->emplace(index, val->clone());
    }

    void Interpreter::fetchDim(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 1, "fetch_dim need exactly one operands");

        Expression* exp = this->resolveVariable(instruction->getOperand(0));
        const u32_t dim = exp->is<ArrayExpression>().ensure("Can only fetch dimension of an array")->getAmount();

        this->pushStack(new NumericExpression(dim));
    }

    void Interpreter::fetch(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 2, "fetch need exactly two operands");

        Expression* exp = this->resolveVariable(instruction->getOperand(0));
        Expression* idx = this->resolveExpression(instruction->getOperand(1));

        const u32_t index = idx->is<NumericExpression>().ensure("Fetch-Index must be numeric")->getAs<u32_t>();
        Expression* val = exp->is<ArrayExpression>().ensure("Need an array to fetch")->fetch(index);

        this->pushStack(val->clone());
    }

    void Interpreter::pop(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 1, "pop need exactly one operand");
        enforce(instruction->getOperand(0)->getType() == OpCode::VARIABLE, "Can only pop into a variable");

        auto val = this->popStack();

        const size_t vi = this->getIndexOf(instruction->getOperand(0));
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

        const f32_t lhs_num = lhs->is<NumericExpression>().ensure("Invalid left hand side expression")->getNumber();
        const f32_t rhs_num = rhs->is<NumericExpression>().ensure("Invalid right hand side expression")->getNumber();

        const i32_t result = lhs_num < rhs_num;
        debug("IS LOWER ", result);
        this->pushStack(new NumericExpression(result));

        return result != 0;
    }

    bool Interpreter::isEqual(Instruction* instruction) {
        enforce(instruction->getOperandAmount() == 2, "is_lower need exactly two operands");

        Expression* lhs = this->resolveExpression(instruction->getOperand(0));
        Expression* rhs = this->resolveExpression(instruction->getOperand(1));

        const f32_t lhs_num = lhs->is<NumericExpression>().ensure("Invalid left hand side expression")->getNumber();
        const f32_t rhs_num = rhs->is<NumericExpression>().ensure("Invalid right hand side expression")->getNumber();

        const i32_t result = std::fabs(lhs_num - rhs_num) < std::numeric_limits<f32_t>::epsilon();
        this->pushStack(new NumericExpression(result));

        return result != 0;
    }

    bool Interpreter::isNotEqual(Instruction* instruction) {
        const bool result = this->isEqual(instruction);

        this->popStack();
        this->pushStack(new NumericExpression(!result));

        return !result;
    }

    bool Interpreter::isLowerOrEqual(Instruction* instruction) {
        return this->isLower(instruction) || this->isEqual(instruction);
    }

    void Interpreter::call(Instruction* instruction, Parser& parser) {
        _backtrack = parser.getIndex();

        this->goTo(instruction, parser);
    }

    void Interpreter::goTo(Instruction* instruction, Parser& parser) {
        enforce(instruction->getOperandAmount() == 1, "goto need exactly one operand");

        Expression* exp = this->resolveExpression(instruction->getOperand(0));

        const std::string& label = exp->is<StringExpression>().ensure("goto need's a string label")->getValue();
        const size_t index = parser.getIndexFor(label);
        debug("goto ", index);

        parser.setIndex(index);
    }

    void Interpreter::goToIf(Instruction* instruction, Parser& parser) {
        auto val = this->popStack();

        const i32_t cond = val->is<NumericExpression>().ensure("Expected a numeric condition")->getAs<i32_t>();
        if (cond) {
            this->goTo(instruction, parser);
        }
    }

    void Interpreter::goToIfNot(Instruction* instruction, Parser& parser) {
        auto val = this->popStack();

        const i32_t cond = val->is<NumericExpression>().ensure("Expected a numeric condition")->getAs<i32_t>();
        if (!cond) {
            this->goTo(instruction, parser);
        }
    }

    Expression* Interpreter::makeExpression(Instruction* instruction) {
        switch (instruction->getType()) {
            case Instruction::ADD: {
                Expression* lhs = this->resolveExpression(instruction->getOperand(0));
                Expression* rhs = this->resolveExpression(instruction->getOperand(1));

                return new AddExpression(lhs->clone(), rhs->clone());
            }
            case Instruction::SUB: {
                Expression* lhs = this->resolveExpression(instruction->getOperand(0));
                Expression* rhs = this->resolveExpression(instruction->getOperand(1));

                return new SubtractExpression(lhs->clone(), rhs->clone());
            }
            case Instruction::MUL: {
                Expression* lhs = this->resolveExpression(instruction->getOperand(0));
                Expression* rhs = this->resolveExpression(instruction->getOperand(1));

                return new MultiplyExpression(lhs->clone(), rhs->clone());
            }
            case Instruction::DIV: {
                Expression* lhs = this->resolveExpression(instruction->getOperand(0));
                Expression* rhs = this->resolveExpression(instruction->getOperand(1));

                return new DivideExpression(lhs->clone(), rhs->clone());
            }
            case Instruction::MOD: {
                Expression* lhs = this->resolveExpression(instruction->getOperand(0));
                Expression* rhs = this->resolveExpression(instruction->getOperand(1));

                return new ModuloExpression(lhs->clone(), rhs->clone());
            }
            case Instruction::NOT: {
                Expression* val = this->resolveExpression(instruction->getOperand(0));

                return new NotExpression(val->clone());
            }
            case Instruction::NEG: {
                Expression* val = this->resolveExpression(instruction->getOperand(0));

                return new NegateExpression(val->clone());
            }
            case Instruction::INC: {
                Expression* val = this->resolveExpression(instruction->getOperand(0));

                return new IncrementExpression(val->clone());
            }
            case Instruction::DEC: {
                Expression* val = this->resolveExpression(instruction->getOperand(0));

                return new DecrementExpression(val->clone());
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
}