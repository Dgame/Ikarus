#include "Interpreter.hpp"
#include "util.hpp"

int main() {
    try {
        Interpreter("assign &0, 42 print &0 append &1, 1 append &1, 2");
    } catch (const char* msg) {
        writeln(msg);
    }
}