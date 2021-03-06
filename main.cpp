#define COMPILE 2
#define TEST 1
#define INTERPRET 0

#define EVAL COMPILE

#include <fstream>
#include <sstream>
#include "util.hpp"

#if EVAL == INTERPRET

#include "Backend/Interpreter.hpp"
#include "Frontend/Parser.hpp"

using Backend::Interpreter;
using Frontend::Parser;

#elif EVAL == TEST
#include "VariableDeclaration.hpp"
#include "NumericExpression.hpp"
#include "ArrayExpression.hpp"
#include "AddExpression.hpp"
#include "MultiplyExpression.hpp"
#include "EvalVisitor.hpp"
#else

#include "Frontend/Parser.hpp"

using Frontend::Parser;

#endif

int main() {
#if EVAL == COMPILE
    try {
        std::ifstream is("D:/Github/Ikarus/main.ik");
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

        Parser parser(&buffer.front(), &buffer.back());
        parser.eval(std::cout);
    } catch (const char* msg) {
        writeln(msg);
    }
#elif EVAL == TEST
    NumericExpression* ne1 = new NumericExpression(42);
    std::unique_ptr<VariableDeclaration> vd1(new VariableDeclaration("a", ne1));

    ArrayExpression* ae1 = new ArrayExpression();
    ae1->append(new NumericExpression(42));
    ae1->append(new NumericExpression(23));
    std::unique_ptr<VariableDeclaration> vd2(new VariableDeclaration("as", ae1));

    AddExpression* m1 = new AddExpression(
            new NumericExpression(23),
            new NumericExpression(42)
    );
    std::unique_ptr<VariableDeclaration> vd3(new VariableDeclaration("a", m1));

    AddExpression* m2 = new AddExpression(
            new AddExpression(
                    new NumericExpression(2),
                    new NumericExpression(3)
            ),
            new NumericExpression(4)
    );
    std::unique_ptr<VariableDeclaration> vd4(new VariableDeclaration("a", m2));

    AddExpression* m3 = new AddExpression(
            new NumericExpression(3),
            new MultiplyExpression(
                    new NumericExpression(4),
                    new NumericExpression(2)
            )
    );
    std::unique_ptr<VariableDeclaration> vd5(new VariableDeclaration("a", m3));

    AddExpression* m4 = new AddExpression(
            new AddExpression(
                    new AddExpression(
                            new NumericExpression(2),
                            new NumericExpression(3)
                    ),
                    new NumericExpression(4)
            ),
            new NumericExpression(5)
    );
    std::unique_ptr<VariableDeclaration> vd6(new VariableDeclaration("a", m4));

    EvalVisitor ev(std::cout);
    vd1->accept(ev);
    vd2->accept(ev);
    vd3->accept(ev);
    vd4->accept(ev);
    vd5->accept(ev);
    vd6->accept(ev);
#elif EVAL == INTERPRET
    try {
        std::ifstream is("D:/Github/Ikarus/test_main.ik");
        if (!is.good())
            throw "Unable to open file";

        std::stringstream buffer;
        buffer << is.rdbuf();

        const std::string str = buffer.str();
        Interpreter(&str.front(), &str.back() + 1);

        //Interpreter("assign &0, 42 print &0 goto L1 append &1, 1 append &1, 2 L1: append &1, 3 print &1 set_index 1 emplace &1, 11 print &1");
    } catch (const char* msg) {
        writeln(msg);
    }
#endif
}