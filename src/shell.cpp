#include "include/util.h"
#include "include/lexer.h"
#include "include/shell.h"

using std::cout, std::endl, std::cin;


void InteractiveShell::prompt() {
    string line;
    print("1.0.0 VIVASVAN INTERACTIVE SHELL");
    print("TYPE COMMANDS HERE");

    while (true) {
        cout << ">> ";
        std::getline(cin, line);
        bool stop_flag = line.find("exit()") != std::string::npos;
        if (stop_flag) {
            break;
        }     

        Lexer lexer;
        lexer.tokenize(line);
    }
}
