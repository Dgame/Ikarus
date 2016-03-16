#include "Interpreter.hpp"
#include "util.hpp"

int main() {
    try {
        Interpreter("assign &0, 42 print &0 goto L1 append &1, 1 append &1, 2 L1: append &1, 3 print &1 set_index 1 emplace &1, 11 print &1");
    } catch (const char* msg) {
        writeln(msg);
    }
}