#include "Backend/VM/Code.hpp"
#include "Backend/VM/Operand.hpp"
#include <sstream>

namespace Backend {
    size_t Code::Labels = 0;

    Code::Code(std::ostream& out) : _out(out) { }

    Code& Code::gen(const std::string& cmd, const Operand& op) {
        _out << cmd << ' ';
        op.print(_out);

        return *this;
    }

    Code& Code::gen(const std::string& cmd, const Operand& lhs, const Operand& rhs) {
        _out << cmd << ' ';
        lhs.print(_out);

        _out << ", ";
        rhs.print(_out);

        return this->end();
    }

    Code& Code::gen(const std::string& cmd, const std::string& op) {
        _out << cmd << ' ' << op << '\n';

        return *this;
    }

    Code& Code::genLabel(const std::string& label) {
        _out << label << ":\n";

        return *this;
    }

    Code& Code::genLabel(size_t id) {
        return this->genLabel(this->label(id));
    }

    std::string Code::label(size_t id) {
        Labels++;

        std::stringstream ss;
        ss << 'L' << id << '_' << Labels;

        return ss.str();
    }
}