#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "include/util.h"
#include "include/lexer.h"

using std::string;

std::vector<string> Lexer::tokenize(string line) {
    std::stringstream *s = new std::stringstream(line);
    std::string token;
    std::vector<std::string> tokens;


    while( std::getline(*s, token, ' ') ) {
        tokens.push_back(token);
    }

    for (std::string token: tokens) {
        print(token);
    }
    delete s;

    return tokens;
}       