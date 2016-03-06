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
                const NumericValue* iv = opc->getValue()->isNumeric();
                enforce(iv != nullptr, "Variable must be numeric offset");

                const u32_t index = iv->get<u32_t>();

                return this->fetchVariable(index);
            }
            case OpCode::OFFSET: {
                const NumericValue* iv = opc->getValue()->isNumeric();
                enforce(iv != nullptr, "Variable must be integer offset");

                const u32_t index = iv->get<u32_t>();

                return this->fetchStack(index);
            }
            case OpCode::VALUE:
                return opc->getValue();
            default:
                enforce(false, "Expected Variable or Offset");
        }

        exit(1);
    }

    void Interpreter::interpret(const std::vector<std::unique_ptr<Command>>& commands) {
        for (auto& cmd : commands) {
            switch (cmd->getType()) {
                case Command::ASSIGN:
                    writeln("CMD ASSIGN");
                    this->assign(cmd.get());
                    break;
                case Command::PUSH:
                    writeln("CMD PUSH");
                    this->push(cmd.get());
                    break;
                case Command::PRINT:
                    writeln("CMD PRINT");
                    this->print(cmd.get());
                    break;
                case Command::ADD:
                    writeln("CMD ADD");
                    this->add(cmd.get());
                    break;
                default:
                    writeln("UNKNOWN");
                    enforce(false, "WTF");
            }
        }
    }

    void Interpreter::assign(const Command* cmd) {
        enforce(cmd->getType() == Command::ASSIGN, "Expected ASSIGN");
        enforce(cmd->getLeft()->getType() == OpCode::VARIABLE, "Left OpCode must be a Variable");
        enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

        const NumericValue* iv = cmd->getLeft()->getValue()->isNumeric();
        enforce(iv != nullptr, "Variable must be integer");

        const Value* value = this->getValue(cmd->getRight());
        const u32_t index = iv->getValue();

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
        enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
        enforce(cmd->getRight() != nullptr, "Right OpCode must not be empty");

        const Value* lhs = this->getValue(cmd->getLeft());
        const Value* rhs = this->getValue(cmd->getRight());

        std::unique_ptr<AddExpression> expr(new AddExpression(lhs, rhs));

        MathExpressionVisitor mev;
        expr->accept(&mev);

        this->pushStack(new NumericValue(mev.getValue()));
    }
}