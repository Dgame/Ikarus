//
// Created by Randy on 05.03.2016.
//

#include "Interpreter.hpp"
#include "Lexer.hpp"
#include "util.hpp"
#include "NumericValue.hpp"
#include "ArrayValue.hpp"
#include "OutputValueVisitor.hpp"
#include "MathExpressionVisitor.hpp"
#include "IndexValueVisitor.hpp"
#include "AssignValueVisitor.hpp"
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
    writeln("<OFFSET ", index, ">");

    return _stack.at(index).get();
}

Value* Interpreter::fetchVariable(u32_t index) const {
    enforce(_variables.size() >= index, "Invalid variable index: ", index);
    writeln("<VARIABLE ", index, ">");

    return _variables.at(index).get();
}

const Value* Interpreter::getValue(const OpCode* opc) const {
    switch (opc->getType()) {
        case OpCode::VARIABLE: {
            IndexValueVisitor ivv;
            opc->getValue()->accept(&ivv);

            return this->fetchVariable(ivv.getIndex());
        }
        case OpCode::OFFSET: {
            IndexValueVisitor ivv;
            opc->getValue()->accept(&ivv);

            return this->fetchStack(ivv.getIndex());
        }
        case OpCode::VALUE:
            return opc->getValue();
        default:
            error("Expected Variable or Offset");
    }

    return nullptr;
}

void Interpreter::interpret(const std::vector<std::unique_ptr<Command>>& commands) {
    writeln("---- INTERPRETER START ----");

    for (u32_t i = 0; i < commands.size(); i++) {
        const Command* cmd = commands.at(i).get();

        switch (cmd->getType()) {
            case Command::ASSIGN:
                writeln("CMD ASSIGN");
                this->assign(cmd);
                break;
            case Command::PUSH:
                writeln("CMD PUSH");
                this->push(cmd);
                break;
            case Command::POP:
                writeln("CMD POP");
                this->pop(cmd);
                break;
            case Command::PRINT:
                writeln("CMD PRINT");
                this->print(cmd);
                break;
            case Command::ADD:
                writeln("CMD ADD");
                this->add(cmd);
                break;
            case Command::SUB:
                writeln("CMD SUB");
                this->sub(cmd);
                break;
            case Command::MUL:
                writeln("CMD MUL");
                this->mul(cmd);
                break;
            case Command::DIV:
                writeln("CMD DIV");
                this->div(cmd);
                break;
            case Command::MOD:
                writeln("CMD MOD");
                this->mod(cmd);
                break;
            case Command::NOT:
                writeln("CMD NOT");
                this->op_not(cmd);
                break;
            case Command::NEG:
                writeln("CMD NEG");
                this->op_neg(cmd);
                break;
            case Command::INC:
                writeln("CMD INC");
                this->op_inc(cmd);
                break;
            case Command::DEC:
                writeln("CMD DEC");
                this->op_dec(cmd);
                break;
            case Command::GOTO:
                writeln("CMD GOTO");
                this->jump(cmd, i);
                break;
            case Command::APPEND:
                writeln("CMD APPEND");
                this->append(cmd);
                break;
            case Command::INDEX:
                writeln("CMD INDEX");
                this->index(cmd);
                break;
            case Command::FETCH:
                writeln("CMD FETCH");
                this->fetch(cmd);
                break;
            default:
                writeln("UNKNOWN");
                error("WTF");
        }
    }

    writeln("---- INTERPRETER FINISHED ----");
}

void Interpreter::assign(const Command* cmd) {
    enforce(cmd->getType() == Command::ASSIGN, "Expected ASSIGN");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    IndexValueVisitor ivv;
    cmd->getLeft()->getValue()->accept(&ivv);

    const Value* value = this->getValue(cmd->getRight());

    writeln("assign variable ", ivv.getIndex(), " with value: ");

    OutputValueVisitor ovv;
    value->accept(&ovv);

    this->assignVariable(ivv.getIndex(), value->clone());
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

    IndexValueVisitor ivv;
    cmd->getLeft()->getValue()->accept(&ivv);

    this->assignVariable(ivv.getIndex(), this->popStack());
}

void Interpreter::print(const Command* cmd) {
    enforce(cmd->getType() == Command::PRINT, "Expected PRINT");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

    const Value* value = this->getValue(cmd->getLeft());

    OutputValueVisitor ovv;
    value->accept(&ovv);
}

void Interpreter::append(const Command* cmd) {
    enforce(cmd->getType() == Command::APPEND, "Expected APPEND");
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    IndexValueVisitor ivv;
    cmd->getLeft()->getValue()->accept(&ivv);

    const Value* item = this->getValue(cmd->getRight());

    // variable does not exists
    if (ivv.getIndex() >= _variables.size()) {
        ArrayValue* av = new ArrayValue();
        av->assign(item->clone());

        this->assignVariable(ivv.getIndex(), av);
    } else {
        Value* value = this->fetchVariable(ivv.getIndex());

        AssignValueVisitor avv(value, item);
        ArrayValue* av = avv.getArrayValue();
        if (av != nullptr) {
            this->assignVariable(ivv.getIndex(), av);
        }
    }
}

void Interpreter::index(const Command* cmd) {
    enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
    enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
    enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

    IndexValueVisitor ivv;
    cmd->getLeft()->getValue()->accept(&ivv);

    Value* value = this->fetchVariable(ivv.getIndex());

    const Value* index = this->getValue(cmd->getRight());
    index->accept(&ivv);

    IndexAssignValueVisitor iavv(ivv.getIndex());
    value->accept(&iavv);
}

void Interpreter::fetch(const Command*) {

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

    switch (jt) {
        case Command::GOTO: {
            IndexValueVisitor ivv;
            cmd->getLeft()->getValue()->accept(&ivv);

            writeln("GOTO ", ivv.getIndex());

            index = ivv.getIndex();
        }
            break;
        default:
            error("Unexpected jump command");
    }
}
