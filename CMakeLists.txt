cmake_minimum_required(VERSION 3.3)
project(Ikarus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        include/Expression/Expression.hpp
        include/Expression/AddExpression.hpp
        src/Expression/BinaryExpression.cpp
        include/Expression/BinaryExpression.hpp
        include/Expression/SubtractExpression.hpp
        include/Expression/MultiplyExpression.hpp
        include/Expression/DivideExpression.hpp
        include/Expression/ModuloExpression.hpp
        include/Expression/NotExpression.hpp
        src/Expression/UnaryExpression.cpp
        include/Expression/UnaryExpression.hpp
        include/Expression/NegateExpression.hpp
        include/Expression/IncrementExpression.hpp
        include/Expression/DecrementExpression.hpp
        include/Visitable.hpp
        include/Visitor/Visitor.hpp
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
        include/Frontend/Lexer.hpp
        src/Frontend/Parser.cpp
        include/Frontend/Parser.hpp
        src/Frontend/Keyword.cpp
        include/Frontend/Keyword.hpp
        include/Expression/BoolExpression.hpp
        include/Expression/LowerExpression.hpp include/Expression/GreaterExpression.hpp include/Expression/LowerEqualExpression.hpp include/Expression/GreaterEqualExpression.hpp include/Expression/EqualExpression.hpp include/Expression/NotEqualExpression.hpp include/Expression/IndexAccessExpression.hpp src/Expression/IndexAssignExpression.cpp include/Expression/IndexAssignExpression.hpp src/Expression/IndexAccessExpression.cpp include/Expression/VariableExpression.hpp)

include_directories("include")
include_directories("include/Expression")
include_directories("include/Declaration")
include_directories("include/Frontend/EvalVisitor")
include_directories("include/Visitor")

add_executable(Ikarus ${SOURCE_FILES})