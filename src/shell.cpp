#include <vector>
#include "include/util.h"
#include "include/lexer.h"
#include "include/shell.h"
#include "include/parser.h"
#include "include/astprinter.h"
#include "include/interpreter.h"
#include "include/stmt.h"


using std::cout, std::endl, std::cin, std::vector;


void InteractiveShell::prompt() {
    string line;
    print("1.0.0 VIVASVAN INTERACTIVE SHELL");
    print("TYPE COMMANDS HERE");
    
    Lexer lexer;
    Parser parser;
    // AstPrinter printer;
    Interpreter interpreter;
    while (true) {
        cout << ">> ";
        std::getline(cin, line);
        bool stop_flag = line.find("exit()") != std::string::npos;
        if (stop_flag) {
            break;
        }     

        lexer.runInteractive(line);
        // lexer.printTokens();
        vector<Token> tokens = lexer.getTokens();
        vector<Stmt*> statements = parser.runInteractive(tokens);

        interpreter.runInteractive(statements[0]);
    }
}
