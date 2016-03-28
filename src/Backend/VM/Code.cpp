#include "Backend/VM/Code.hpp"
#include "Backend/VM/Operand.hpp"

namespace Backend {
    Code::Code(std::ostream& out) : _out(out) { }

    void Code::gen(const std::string& cmd, const Operand& op, bool nl) {
        _out << cmd << ' ';
        op.print(_out);

        if (nl) {
            _out << std::endl;
        }
    }

    void Code::gen(const std::string& cmd, const Operand& lhs, const Operand& rhs) {
        _out << cmd << ' ';
        lhs.print(_out);
        _out << ", ";
        rhs.print(_out);
        _out << std::endl;
    }
}