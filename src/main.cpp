#include <iostream>
#include <sstream>
#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/shell.h"
#include "include/allexpr.h"
#include "include/astprinter.h"

using std::cout, std::endl, std::cin;
using std::string;


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        InteractiveShell shell;
        shell.prompt();
        return 0;
    }
    string filename = argv[1];

    Lexer lexer(filename);
    lexer.readygo();
    lexer.printTokens();

    // Object n1 = std::stof("122.0");
    // Object n2 = std::stof("132.0");

    // Expr<string>* l1 = new Literal<string>(&n1);
    // Expr<string>* l2 = new Literal<string>(&n2);

    // Expr<string>* l11 = new Unary<string>(new Token(TokenType::MINUS, "-", "", 1), l1);

    // Expr<string>* expression = new Binary<string>(l11, new Token(TokenType::PLUS, "+", "", 1), l2);

    // AstPrinter<string> printer;
    // string value = printer.print(expression);
    // print(value);


    return 0;
}

