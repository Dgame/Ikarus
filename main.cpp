#include "Backend/include/Interpreter.hpp"

using ik::Interpreter;

int main() {
    Interpreter("assign &1, 42 print &1 add &1, 23 assign &1, ~0 print &1");
}