#include <iostream>
#include "Interpreter.hpp"

#define DEBUG false

int main() {
//    Interpreter("assign &0, 42 print &0 add &0, 23 print ~0 assign &0, ~0 print &0 inc &0 pop &0 print &0");
    Interpreter("assign &0, 42 print &0");
    std::cout << std::string(50, '*') << std::endl;

    Interpreter("assign &0, 42 add &0, 23 print ~0");
    std::cout << std::string(50, '*') << std::endl;

    Interpreter("assign &0, 42 add &0, 23 pop &0 print &0");
    std::cout << std::string(50, '*') << std::endl;

    Interpreter("assign &0, 42 add &0, 23 assign &0, ~0 print &0");
    std::cout << std::string(50, '*') << std::endl;

    Interpreter("assign &0, 42 inc &0 pop &0 print &0");
    std::cout << std::string(50, '*') << std::endl;
}