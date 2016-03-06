//
// Created by Randy on 05.03.2016.
//

#include <Interpreter.hpp>
#include <Lexer.hpp>
#include <util.hpp>
#include <NumericValue.hpp>
#include <OutputValueVisitor.hpp>
#include <MathExpressionVisitor.hpp>
#include <AddExpression.hpp>

namespace ik {
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

    const Value* Interpreter::popStack() {
        _stack_offset--;

        return this->fetchStack(_stack_offset);
    }

    const Value* Interpreter::fetchStack(u32_t index) const {
        enforce(_stack.size() >= index, "Invalid offset index: ", index);
        writeln("<OFFSET ", index, ">");

        return _stack.at(index).get();
    }

    const Value* Interpreter::fetchVariable(u32_t index) const {
        enforce(_variables.size() >= index, "Invalid variable index: ", index);
        writeln("<VARIABLE ", index, ">");

        return _variables.at(index).get();
    }

    const Value* Interpreter::getValue(const OpCode* opc) const {
        switch (opc->getType()) {
            case OpCode::VARIABLE: {
                const NumericValue* nv = opc->getValue()->isNumeric();
                enforce(nv != nullptr, "Variable must be numeric offset");

                const u32_t index = nv->get<u32_t>();

                return this->fetchVariable(index);
            }
            case OpCode::OFFSET: {
                const NumericValue* nv = opc->getValue()->isNumeric();
                enforce(nv != nullptr, "Variable must be integer offset");

                const u32_t index = nv->get<u32_t>();

                return this->fetchStack(index);
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
                case Command::PRINT:
                    writeln("CMD PRINT");
                    this->print(cmd);
                    break;
                case Command::ADD:
                    writeln("CMD ADD");
                    this->add(cmd);
                    break;
                case Command::GOTO:
                    writeln("CMD GOTO");
                    this->jump(cmd, i);
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
        enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
        enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

        const NumericValue* nv = cmd->getLeft()->getValue()->isNumeric();
        enforce(nv != nullptr, "Variable must be integer");

        const Value* value = this->getValue(cmd->getRight());
        const u32_t index = nv->get<u32_t>();

        writeln("assign variable ", index, " with value: ");

        OutputValueVisitor ovv;
        value->accept(&ovv);

        this->assignVariable(index, value->clone());
    }

    void Interpreter::push(const Command* cmd) {
        enforce(cmd->getType() == Command::PUSH, "Expected PUSH");
        enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
        enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

        const Value* value = this->getValue(cmd->getLeft());

        this->pushStack(value->clone());
    }

    void Interpreter::print(const Command* cmd) {
        enforce(cmd->getType() == Command::PRINT, "Expected PRINT");
        enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
        enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

        const Value* value = this->getValue(cmd->getLeft());

        OutputValueVisitor ovv;
        value->accept(&ovv);
    }

    void Interpreter::add(const Command* cmd) {
        enforce(cmd->getType() == Command::ADD, "Expected ADD");

        this->math(cmd);
    }

    const Expression* Interpreter::makeExpression(const Command* cmd) {
        const Value* lhs = this->getValue(cmd->getLeft());
        const Value* rhs = this->getValue(cmd->getRight());

        switch (cmd->getType()) {
            case Command::ADD:
                return new AddExpression(lhs, rhs);
//            case Command::SUB:
//            case Command::MUL:
//            case Command::DIV:
//            case Command::MOD:
            default:
                error("Invalid math expression");
        }

        return nullptr;
    }

    void Interpreter::math(const Command* cmd) {
        enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
        enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

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
                const Value* value = this->getValue(cmd->getLeft());

                const NumericValue* nv = value->isNumeric();
                enforce(nv != nullptr, "Need numeric value");

                writeln("GOTO ", nv->get<u32_t>());

                index = nv->get<u32_t>();
            }
                break;
            default:
                error("Unexpected jump command");
        }
    }
}