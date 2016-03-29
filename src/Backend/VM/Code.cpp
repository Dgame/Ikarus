#include "Backend/VM/Code.hpp"
#include "Backend/VM/Operand.hpp"
#include <sstream>

namespace Backend {
    size_t Code::Labels = 0;

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

    void Code::gen(const std::string& cmd, const std::string& op) {
        _out << cmd << ' ' << op << std::endl;
    }

    void Code::genLabel(const std::string& label) {
        _out << label << ':' << std::endl;
    }

    void Code::genLabel(size_t id) {
        this->genLabel(this->label(id));
    }

    std::string Code::label(size_t id) {
        Labels++;

        std::stringstream ss;
        ss << 'L' << id << '_' << Labels;

        return ss.str();
    }
}