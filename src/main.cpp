#include <iostream>
#include <sstream>
#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/shell.h"
#include "include/allexpr.h"
#include "include/astprinter.h"
#include "include/parser.h"
#include "include/interpreter.h"
#include "include/stmt.h"

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
    vector<Token> tokens = lexer.getTokens();

    Parser parser(tokens);
    vector<Stmt*> statements = parser.parse();

    Interpreter interpreter(statements);
    interpreter.interpret();

    return 0;
}
