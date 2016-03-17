#include <fstream>
#include "Interpreter.hpp"
#include "util.hpp"

using Backend::Interpreter;

int main() {
    try {
        std::ifstream is("C:/Users/Bjarne/Documents/GitHub/Ikarus.git/func.ik");
        if (!is.good())
            throw "Unable to open file";
        /*
         * Get the size of the file
         */
        is.seekg(0, std::ios::end);
        auto len = static_cast<i32_t>(is.tellg());
        if (len <= 0)
            throw "Empty file";

        const u32_t size = static_cast<u32_t>(len);

        is.seekg(0, std::ios::beg);
        /*
         * Read the whole file into the buffer.
         */
        std::vector<char> buffer(size);
        is.read(&buffer[0], size);

        Interpreter(&buffer.front(), &buffer.back());

        //Interpreter("assign &0, 42 print &0 goto L1 append &1, 1 append &1, 2 L1: append &1, 3 print &1 set_index 1 emplace &1, 11 print &1");
    } catch (const char* msg) {
        writeln(msg);
    }
}