#ifndef IKARUS_VMCODE_HPP
#define IKARUS_VMCODE_HPP

#include <string>
#include <iostream>

namespace Backend {
    class Operand;

    class Code {
    private:
        static size_t Labels;

        std::ostream& _out;

    public:
        explicit Code(std::ostream&);

        void gen(const std::string&, const Operand&, bool nl = true);

        void gen(const std::string&, const Operand&, const Operand&);

        void gen(const std::string&, const std::string&);

        void genLabel(const std::string&);
        void genLabel(size_t);

        std::string label(size_t);
    };
}

#endif //IKARUS_VMCODE_HPP
