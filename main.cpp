#include "Interpreter.hpp"
#include "util.hpp"

int main() {
    try {
        Interpreter("assign &0, 42 print &0 append &1, 1 append &1, 2 append &1, 3 print &1 push 1 emplace &1, 11 print &1");
    } catch (const char* msg) {
        writeln(msg);
    }
}