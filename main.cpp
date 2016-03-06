#include "Backend/include/Interpreter.hpp"

using ik::Interpreter;

int main() {
    Interpreter("assign &0, 42 print &0 goto 5 add &0, 23 print ~0 assign &0, ~0 print &0");
}