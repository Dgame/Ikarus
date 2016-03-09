//
// Created by Randy on 05.03.2016.
//

#include "Interpreter.hpp"
#include "Lexer.hpp"
#include "util.hpp"
#include "NumericValue.hpp"
#include "ArrayValue.hpp"
#include "NumericValueVisitor.hpp"
#include "MathExpressionVisitor.hpp"
#include "ValueRevelation.hpp"
#include "AddExpression.hpp"
#include "SubExpression.hpp"
#include "MulExpression.hpp"
#include "DivExpression.hpp"
#include "ModExpression.hpp"
#include "NotExpression.hpp"
#include "NegExpression.hpp"
#include "IncExpression.hpp"
#include "DecExpression.hpp"

Interpreter::Interpreter(const std::string& str) : _variables(8), _stack(8) {
    Lexer lex(str);

    this->interpret(lex.getCommands());
}

void Interpreter::assignVariable(u32_t index, Value* value) {
    if (index >= _variables.size()) {
        _variables.resize(index * 2);
    }

    _variables.at(index).reset(value);
}

void Interpreter::pushStack(Value* value) {
    if (_stack_offset >= _stack.size()) {
        _stack.resize(_stack_offset * 2);
    }

    _stack.at(_stack_offset).reset(value);
    _stack_offset++;
}

Value* Interpreter::popStack() {
    _stack_offset--;

    return _stack.at(_stack_offset).release();
}

const Value* Interpreter::fetchStack(u32_t index) const {
    enforce(_stack.size() >= index, "Invalid offset index: ", index);
    debug("<OFFSET ", index, ">");

    return _stack.at(index).get();
}

Value* Interpreter::fetchVariable(u32_t index) const {
    enforce(_variables.size() >= index, "Invalid variable index: ", index);
    debug("<VARIABLE ", index, ">");

    return _variables.at(index).get();
}

const Value* Interpreter::getValue(const OpCode* opc) const {
    switch (opc->getType()) {
        case OpCode::VARIABLE: {
            NumericValueVisitor nvv;
            opc->getValue()->accept(nvv);

            return this->fetchVariable(nvv.getIndex());
        }
        case OpCode::OFFSET: {
            NumericValueVisitor nvv;
            opc->getValue()->accept(nvv);

            return this->fetchStack(nvv.getIndex());
        }
        case OpCode::VALUE:
            return opc->getValue();
        default:
            error("Expected Variable or Offset");
    }

    return nullptr;
}

i32_t Interpreter::interpret(const std::vector<std::unique_ptr<Command>>& commands) {
    debug("---- INTERPRETER START ----");

    for (u32_t i = 0; i < commands.size(); i++) {
        const Command* cmd = commands.at(i).get();

        switch (cmd->getType()) {
            default:
                debug("UNKNOWN");
                error("WTF");
                return 1;
            case Command::EXIT:
                return this->exit(cmd);
            case Command::ASSIGN:
                debug("CMD ASSIGN");
                this->assign(cmd);
                break;
            case Command::PUSH:
                debug("CMD PUSH");
                this->push(cmd);
                break;
            case Command::POP:
                debug("CMD POP");
                this->pop(cmd);
                break;
            case Command::PRINT:
                debug("CMD PRINT");
                this->print(cmd);
                break;
            case Command::ADD:
                debug("CMD ADD");
                this->add(cmd);
                break;
            case Command::SUB:
                debug("CMD SUB");
                this->sub(cmd);
                break;
            case Command::MUL:
                debug("CMD MUL");
                this->mul(cmd);
                break;
            case Command::DIV:
                debug("CMD DIV");
                this->div(cmd);
                break;
            case Command::MOD:
                debug("CMD MOD");
                this->mod(cmd);
                break;
            case Command::NOT:
                debug("CMD NOT");
                this->op_not(cmd);
                break;
            case Command::NEG:
                debug("CMD NEG");
                this->op_neg(cmd);
                break;
            case Command::INC:
                debug("CMD INC");
                this->op_inc(cmd);
                break;
            case Command::DEC:
                debug("CMD DEC");
                this->op_dec(cmd);
                break;
            case Command::JUMP:
            case Command::JUMP_IF:
            case Command::JUMP_IF_NOT:
                debug("CMD JUMP");
                this->jump(cmd, i);
                break;
            case Command::IS_LOWER:
                debug("CMD IS_LOWER");
                this->is_lower(cmd);
                break;
            case Command::IS_EQUAL:
                debug("CMD IS_EQUAL");
                this->is_equal(cmd);
                break;
            case Command::IS_LOWER_OR_EQUAL:
                debug("CMD IS_LOWER_OR_EQUAL");
                this->is_lower_or_equal(cmd);
                break;
            case Command::APPEND:
                debug("CMD APPEND");
                this->append(cmd);
                break;
            case Command::INDEX:
                debug("CMD INDEX");
                this->index(cmd);
                break;
            case Command::FETCH:
                debug("CMD FETCH");
                this->fetch(cmd);
                break;
        }
    }

    debug("---- INTERPRETER FINISHED ----");

    return 0;
}

i32_t Interpreter::exit(const Command* cmd) {
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    return static_cast<i32_t>(nvv.getNumber());
}

void Interpreter::assign(const Command* cmd) {
    enforce(cmd->getType() == Command::ASSIGN, "Expected ASSIGN");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    const Value* value = this->getValue(cmd->getRight());
    debug("assign variable ", nvv.getIndex(), " with value: ");
#if DEBUG
    value->output(std::cout) << std::endl;
#endif

    this->assignVariable(nvv.getIndex(), value->clone());
}

void Interpreter::push(const Command* cmd) {
    enforce(cmd->getType() == Command::PUSH, "Expected PUSH");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    const Value* value = this->getValue(cmd->getLeft());

    this->pushStack(value->clone());
}

void Interpreter::pop(const Command* cmd) {
    enforce(cmd->getType() == Command::POP, "Expected POP");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    this->assignVariable(nvv.getIndex(), this->popStack());
}

void Interpreter::print(const Command* cmd) {
    enforce(cmd->getType() == Command::PRINT, "Expected PRINT");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    const Value* value = this->getValue(cmd->getLeft());
    value->output(std::cout) << std::endl;
}

void Interpreter::append(const Command* cmd) {
    enforce(cmd->getType() == Command::APPEND, "Expected APPEND");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    const Value* item = this->getValue(cmd->getRight());

    // variable does not exists
    if (nvv.getIndex() >= _variables.size()) {
        ArrayValue* av = new ArrayValue();
        av->assign(item->clone());

        this->assignVariable(nvv.getIndex(), av);
    } else {
        Value* value = this->fetchVariable(nvv.getIndex());
        MutableValueRevelation mvr;
        value->accept(mvr);

        if (mvr.array != nullptr) {
            mvr.array->assign(item->clone());
        } else {
            ArrayValue* av = new ArrayValue();
            av->assign(value->clone());
            av->assign(item->clone());

            this->assignVariable(nvv.getIndex(), av);
        }
    }
}

void Interpreter::index(const Command* cmd) {
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    const Value* index = this->getValue(cmd->getRight());
    index->accept(nvv);

    Value* value = this->fetchVariable(nvv.getIndex());
    MutableValueRevelation mvr;
    value->accept(mvr);

    if (mvr.array != nullptr) {
        mvr.array->setIndex(nvv.getIndex());
    } else {
        error("Need Array to set index");
    }
}

void Interpreter::fetch(const Command* cmd) {
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    const Value* index = this->getValue(cmd->getRight());
    index->accept(nvv);

    Value* value = this->fetchVariable(nvv.getIndex());
    MutableValueRevelation mvr;
    value->accept(mvr);

    if (mvr.array != nullptr) {
        const Value* item = mvr.array->fetch(nvv.getIndex());
        this->pushStack(item->clone());
    } else {
        error("Need Array to fetch index");
    }
}

void Interpreter::add(const Command* cmd) {
    enforce(cmd->getType() == Command::ADD, "Expected ADD");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    this->math(cmd);
}

void Interpreter::sub(const Command* cmd) {
    enforce(cmd->getType() == Command::SUB, "Expected SUB");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    this->math(cmd);
}

void Interpreter::mul(const Command* cmd) {
    enforce(cmd->getType() == Command::MUL, "Expected MUL");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    this->math(cmd);
}

void Interpreter::div(const Command* cmd) {
    enforce(cmd->getType() == Command::DIV, "Expected DIV");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    this->math(cmd);
}

void Interpreter::mod(const Command* cmd) {
    enforce(cmd->getType() == Command::MOD, "Expected MOD");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    this->math(cmd);
}

void Interpreter::op_not(const Command* cmd) {
    enforce(cmd->getType() == Command::NOT, "Expected NOT");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    this->math(cmd);
}

void Interpreter::op_neg(const Command* cmd) {
    enforce(cmd->getType() == Command::NEG, "Expected NEG");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    this->math(cmd);
}

void Interpreter::op_inc(const Command* cmd) {
    enforce(cmd->getType() == Command::INC, "Expected INC");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    this->math(cmd);
}

void Interpreter::op_dec(const Command* cmd) {
    enforce(cmd->getType() == Command::DEC, "Expected DEC");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    this->math(cmd);
}

bool Interpreter::is_lower(const Command* cmd) {
    enforce(cmd->getType() == Command::IS_LOWER, "Expected IS_LOWER");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    const Value* lhs = this->getValue(cmd->getLeft());
    const Value* rhs = this->getValue(cmd->getRight());

    _compare = lhs->compare(rhs) == Compare::IS_LOWER;
    writeln("is_lower: ", static_cast<i32_t>(_compare));

    return _compare;
}

bool Interpreter::is_equal(const Command* cmd) {
    enforce(cmd->getType() == Command::IS_EQUAL, "Expected IS_EQUAL");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    const Value* lhs = this->getValue(cmd->getLeft());
    const Value* rhs = this->getValue(cmd->getRight());

    _compare = lhs->compare(rhs) == Compare::IS_EQUAL;
    writeln("is_equal: ", static_cast<i32_t>(_compare));

    return _compare;
}

bool Interpreter::is_lower_or_equal(const Command* cmd) {
    enforce(cmd->getType() == Command::IS_LOWER_OR_EQUAL, "Expected IS_LOWER_OR_EQUAL");

    if (!this->is_lower(cmd)) {
        return this->is_equal(cmd);
    }

    return true;
}

const Expression* Interpreter::makeExpression(const Command* cmd) {
    switch (cmd->getType()) {
        case Command::ADD: {
            const Value* lhs = this->getValue(cmd->getLeft());
            const Value* rhs = this->getValue(cmd->getRight());

            return new AddExpression(lhs, rhs);
        }
        case Command::SUB: {
            const Value* lhs = this->getValue(cmd->getLeft());
            const Value* rhs = this->getValue(cmd->getRight());

            return new SubExpression(lhs, rhs);
        }
        case Command::MUL: {
            const Value* lhs = this->getValue(cmd->getLeft());
            const Value* rhs = this->getValue(cmd->getRight());

            return new MulExpression(lhs, rhs);
        }
        case Command::DIV: {
            const Value* lhs = this->getValue(cmd->getLeft());
            const Value* rhs = this->getValue(cmd->getRight());

            return new DivExpression(lhs, rhs);
        }
        case Command::MOD: {
            const Value* lhs = this->getValue(cmd->getLeft());
            const Value* rhs = this->getValue(cmd->getRight());

            return new ModExpression(lhs, rhs);
        }
        case Command::NOT: {
            const Value* value = this->getValue(cmd->getLeft());

            return new NotExpression(value);
        }
        case Command::NEG: {
            const Value* value = this->getValue(cmd->getLeft());

            return new NegExpression(value);
        }
        case Command::INC: {
            const Value* value = this->getValue(cmd->getLeft());

            return new IncExpression(value);
        }
        case Command::DEC: {
            const Value* value = this->getValue(cmd->getLeft());

            return new DecExpression(value);
        }
        default:
            error("Invalid math expression");
    }

    return nullptr;
}

void Interpreter::math(const Command* cmd) {
    std::unique_ptr<const Expression> expr(this->makeExpression(cmd));

    MathExpressionVisitor mev;
    expr->accept(&mev);

    this->pushStack(new NumericValue(mev.getValue()));
}

void Interpreter::jump(const Command* cmd, u32_t& index) {
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    auto jt = cmd->isJump();
    enforce(jt != Command::NONE, "Invalid jump command");

    NumericValueVisitor nvv;
    cmd->getLeft()->getValue()->accept(nvv);

    switch (jt) {
        case Command::JUMP:
            debug("JUMP ", nvv.getIndex());
            index = nvv.getIndex();
            break;
        case Command::JUMP_IF:
            debug("JUMP IF ", nvv.getIndex());
            if (_compare)
                index = nvv.getIndex();
            break;
        case Command::JUMP_IF_NOT:
            debug("JUMP IF NOT ", nvv.getIndex());
            if (!_compare)
                index = nvv.getIndex();
            break;
        default:
            error("Unexpected jump command");
    }
}
