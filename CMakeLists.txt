cmake_minimum_required(VERSION 3.3)
project(Ikarus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        main.cpp
        Backend/src/Lexer.cpp
        Backend/include/Lexer.hpp
        Backend/include/util.hpp
        Backend/src/OpCode.cpp
        Backend/include/OpCode.hpp
        Backend/src/Command.cpp
        Backend/include/Command.hpp
        Backend/src/Interpreter.cpp
        Backend/include/Interpreter.hpp
        Backend/include/Value/Value.hpp
        Backend/include/Value/NumericValue.hpp
        Backend/include/Visitor/ImmutableValueVisitor.hpp
        Backend/src/Value/NumericValue.cpp
        Backend/include/Visitor/ExpressionVisitor.hpp
        Backend/include/Expression/Expression.hpp
        Backend/src/Expression/AddExpression.cpp
        Backend/include/Expression/AddExpression.hpp
        Backend/src/Visitor/MathExpressionVisitor.cpp
        Backend/include/Visitor/MathExpressionVisitor.hpp
        Backend/include/types.hpp
        Backend/include/unique.hpp
        Backend/src/Expression/BinaryExpression.cpp
        Backend/include/Expression/BinaryExpression.hpp
        Backend/src/Expression/SubExpression.cpp
        Backend/include/Expression/SubExpression.hpp
        Backend/src/Expression/MulExpression.cpp
        Backend/include/Expression/MulExpression.hpp
        Backend/src/Expression/DivExpression.cpp
        Backend/include/Expression/DivExpression.hpp
        Backend/src/Expression/ModExpression.cpp
        Backend/include/Expression/ModExpression.hpp
        Backend/src/Expression/NotExpression.cpp
        Backend/include/Expression/NotExpression.hpp
        Backend/src/Expression/UnaryExpression.cpp
        Backend/include/Expression/UnaryExpression.hpp
        Backend/src/Expression/NegExpression.cpp
        Backend/include/Expression/NegExpression.hpp
        Backend/src/Expression/IncExpression.cpp
        Backend/include/Expression/IncExpression.hpp
        Backend/src/Expression/DecExpression.cpp
        Backend/include/Expression/DecExpression.hpp
        Backend/src/Value/ArrayValue.cpp
        Backend/include/Value/ArrayValue.hpp
        Backend/include/Visitor/MutableValueVisitor.hpp
        Backend/src/Visitor/AssignValueVisitor.cpp
        Backend/include/Visitor/AssignValueVisitor.hpp
        Backend/src/Visitor/NumericValueVisitor.cpp
        Backend/include/Visitor/NumericValueVisitor.hpp
        Backend/include/Visitor/ValueRevelation.hpp)

include_directories("Backend/include")
include_directories("Backend/include/Value")
include_directories("Backend/include/Expression")
include_directories("Backend/include/Visitor")

add_executable(Ikarus ${SOURCE_FILES})