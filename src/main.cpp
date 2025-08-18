#include <iostream>
#include <sstream>
#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/shell.h"
#include "include/allexpr.h"
#include "include/astprinter.h"
#include "include/parser.h"

using std::cout, std::endl, std::cin;
using std::string, std::vector;


int main(int argc, char* argv[]) {

    if (argc < 2) {
        InteractiveShell shell;
        shell.prompt();
        return 0;
    }
    string filename = argv[1];

    Lexer lexer(filename);
    lexer.readygo();
    // lexer.printTokens();
    // print("=========================================================");
    vector<Token> tokens = lexer.getTokens();
    Parser parser(tokens);
    Expr* expression = parser.parse();

    AstPrinter printer;
    string value = printer.prints(expression);
    print(value);

    return 0;
}
