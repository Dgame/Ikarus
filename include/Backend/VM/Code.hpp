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

        Code& end() {
            _out << '\n';

            return *this;
        }

        Code& gen(const std::string&, const Operand&);

        Code& gen(const std::string&, const Operand&, const Operand&);

        Code& gen(const std::string&, const std::string&);

        Code& genLabel(const std::string&);

        Code& genLabel(size_t);

        std::string label(size_t);
    };
}

#endif //IKARUS_VMCODE_HPP
