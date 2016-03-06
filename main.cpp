#include "Backend/include/Interpreter.hpp"

using ik::Interpreter;

int main() {
    Interpreter("assign &1, 42 print &1 goto 5 add &1, 23 print ~0 assign &1, ~0 print &1");
}