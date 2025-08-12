#include <iostream>
#include <sstream>
#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/shell.h"

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

    return 0;
}

