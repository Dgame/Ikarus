cmake_minimum_required(VERSION 3.3)
project(Ikarus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        include/Expression/Expression.hpp
        src/Expression/AddExpression.cpp
        include/Expression/AddExpression.hpp
        src/Expression/BinaryExpression.cpp
        include/Expression/BinaryExpression.hpp
        src/Expression/SubtractExpression.cpp
        include/Expression/SubtractExpression.hpp
        src/Expression/MultiplyExpression.cpp
        include/Expression/MultiplyExpression.hpp
        src/Expression/DivideExpression.cpp
        include/Expression/DivideExpression.hpp
        src/Expression/ModuloExpression.cpp
        include/Expression/ModuloExpression.hpp
        src/Expression/NotExpression.cpp
        include/Expression/NotExpression.hpp
        src/Expression/UnaryExpression.cpp
        include/Expression/UnaryExpression.hpp
        src/Expression/NegateExpression.cpp
        include/Expression/NegateExpression.hpp
        src/Expression/IncrementExpression.cpp
        include/Expression/IncrementExpression.hpp
        src/Expression/DecrementExpression.cpp
        include/Expression/DecrementExpression.hpp
        include/Visitable.hpp
        include/Visitor/Visitor.hpp
        src/Expression/NumericExpression.cpp
        include/Expression/NumericExpression.hpp
        include/types.hpp
        include/unique.hpp
        include/util.hpp
        src/Expression/ArrayExpression.cpp
        include/Expression/ArrayExpression.hpp
        src/Declaration/Declaration.cpp
        include/Declaration/Declaration.hpp
        include/StorageClass.hpp
        include/Declaration/VariableDeclaration.hpp
        src/Visitor/OutputVisitor.cpp
        include/Visitor/OutputVisitor.hpp
        src/Visitor/MathVisitor.cpp
        include/Visitor/MathVisitor.hpp
        src/Backend/Lexer.cpp
        include/Backend/Lexer.hpp
        include/Token.hpp
        src/Token.cpp
        src/Backend/Interpreter.cpp
        include/Backend/Interpreter.hpp
        src/Backend/Parser.cpp
        include/Backend/Parser.hpp
        src/Backend/Instruction.cpp
        include/Backend/Instruction.hpp
        src/Backend/OpCode.cpp
        include/Backend/OpCode.hpp
        include/Visitor/RevelationVisitor.hpp
        src/Expression/StringExpression.cpp
        include/Expression/StringExpression.hpp
        src/AbstractLexer.cpp
        include/AbstractLexer.hpp
        include/NullExpression.hpp
        include/Frontend/Evaluable.hpp
        include/Visitor/EvalVisitor.hpp
        src/Declaration/VariableDeclaration.cpp
        src/Visitor/EvalVisitor.cpp
        src/Frontend/Scope.cpp
        include/Frontend/Scope.hpp
        src/Frontend/Lexer.cpp
        include/Frontend/Lexer.hpp src/Frontend/Parser.cpp include/Frontend/Parser.hpp src/Frontend/Keyword.cpp include/Frontend/Keyword.hpp)

include_directories("include")
include_directories("include/Expression")
include_directories("include/Declaration")
include_directories("include/Frontend/EvalVisitor")
include_directories("include/Visitor")

add_executable(Ikarus ${SOURCE_FILES})