#include <iostream>
#include "include/util.h"
#include "include/token.h"
#include "include/lexer.h"
#include "include/shell.h"
#include "sstream"
#include "fstream"

using std::cout, std::endl, std::cin;
using std::string;


int main(int argc, char* argv[]) {
    
    if (argc < 2) {
        InteractiveShell shell;
        shell.prompt();
        return 0;
    }
    string filename = argv[1];

    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error: Could not open the file!\n";
        return 1;
    }

    string line;
    Lexer lexer;

    while (getline(file, line)) {
        lexer.tokenize(line);
    }

    return 0;
}

