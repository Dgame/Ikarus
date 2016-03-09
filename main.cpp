#include "Interpreter.hpp"
#include "util.hpp"

#define DEBUG false

int main() {
//    Interpreter("assign &0, 42 print &0 add &0, 23 print ~0 assign &0, ~0 print &0 inc &0 pop &0 print &0");
    try {
        Interpreter("assign &0, 42 print &0");
        writeln(std::string(50, '*'));

        Interpreter("assign &0, 42 add &0, 23 print ~0");
        writeln(std::string(50, '*'));

        Interpreter("assign &0, 42 add &0, 23 pop &0 print &0");
        writeln(std::string(50, '*'));

        Interpreter("assign &0, 42 add &0, 23 assign &0, ~0 print &0");
        writeln(std::string(50, '*'));

        Interpreter("assign &0, 42 inc &0 pop &0 print &0");
        writeln(std::string(50, '*'));

        Interpreter("assign &0, 42 is_lower &0, 23 jump_if 4 inc &0 pop &0 print &0");
        writeln(std::string(50, '*'));
    } catch (const char* msg) {
        writeln(msg);
    }
}