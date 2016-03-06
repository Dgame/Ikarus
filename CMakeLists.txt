cmake_minimum_required(VERSION 3.3)
project(Ikarus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Backend/src/Lexer.cpp Backend/include/Lexer.hpp Backend/include/util.hpp Backend/src/OpCode.cpp Backend/include/OpCode.hpp Backend/src/Command.cpp Backend/include/Command.hpp Backend/src/Interpreter.cpp Backend/include/Interpreter.hpp Backend/include/Value/Value.hpp Backend/include/Value/IntegerValue.hpp Backend/include/Visitor/ValueVisitor.hpp Backend/src/Value/IntegerValue.cpp Backend/src/Visitor/OutputValueVisitor.cpp Backend/include/Visitor/OutputValueVisitor.hpp Backend/include/Visitor/ExpressionVisitor.hpp Backend/include/Expression/Expression.hpp Backend/src/Expression/AddExpression.cpp Backend/include/Expression/AddExpression.hpp Backend/src/Visitor/MathExpressionVisitor.cpp Backend/include/Visitor/MathExpressionVisitor.hpp)
add_executable(Ikarus ${SOURCE_FILES})