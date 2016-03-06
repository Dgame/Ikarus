//
// Created by Randy on 05.03.2016.
//

#include "../include/Interpreter.hpp"
#include "../include/Lexer.hpp"
#include "../include/util.hpp"
#include "../include/Value/IntegerValue.hpp"
#include "../include/Visitor/OutputValueVisitor.hpp"
#include "../include/Visitor/MathExpressionVisitor.hpp"
#include "../include/Expression/AddExpression.hpp"

namespace ik {
    Interpreter::Interpreter(const std::string& str) : _variables(8), _stack(8) {
        Lexer lex(str);

        this->interpret(lex.getCommands());
    }

    const Value* Interpreter::getValue(const OpCode* opc) const {
        switch (opc->getType()) {
            case OpCode::VARIABLE: {
                const IntegerValue* iv = opc->getValue()->isInteger();
                enforce(iv != nullptr, "Variable must be integer offset");

                const int index = iv->getValue();

                enforce(_variables.size() > index, "Invalid variable index: ", index);
                writeln("<VARIABLE ", index, ">");

                return _variables[index].get();
            }
            case OpCode::OFFSET: {
                const IntegerValue* iv = opc->getValue()->isInteger();
                enforce(iv != nullptr, "Variable must be integer offset");

                const int index = iv->getValue();

                enforce(_stack.size() > index, "Invalid offset index: ", index);
                writeln("<OFFSET ", index, ">");

                return _stack[index].get();
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

        const IntegerValue* iv = cmd->getLeft()->getValue()->isInteger();
        enforce(iv != nullptr, "Variable must be integer");

        const Value* value = this->getValue(cmd->getRight());
        const int index = iv->getValue();

        writeln("assign variable ", index, " with value: ");

        OutputValueVisitor ovv;
        value->accept(&ovv);

        if (index >= _variables.size()) {
            _variables.resize(static_cast<unsigned>(index + 1));
        }

        _variables[index].reset(value->clone());
    }

    void Interpreter::push(const Command* cmd) {
        enforce(cmd->getType() == Command::PUSH, "Expected PUSH");
        enforce(cmd->getLeft() != nullptr, "Left OpCode must not be empty");
        enforce(cmd->getRight() == nullptr, "Right OpCode must be empty");

        const Value* value = this->getValue(cmd->getLeft());

        _stack.emplace_back(value->clone());
        _stack_offset++;
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

        _stack.emplace_back(new IntegerValue(mev.getValue()));
        _stack_offset++;
    }
}