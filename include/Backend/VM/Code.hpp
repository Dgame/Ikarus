#ifndef IKARUS_VMCODE_HPP
#define IKARUS_VMCODE_HPP

#include <string>
#include <iostream>

namespace Backend {
    class Operand;

    class Code {
    private:
        std::ostream& _out;

    public:
        explicit Code(std::ostream&);

        void gen(const std::string&, const Operand&, bool nl = true);

        void gen(const std::string&, const Operand&, const Operand&);
    };
}

#endif //IKARUS_VMCODE_HPP
