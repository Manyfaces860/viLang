#include <iostream>
#include <vector>
#include <string>

using std::string;

class Lexer {
    public:
        std::vector<string> tokenize(string line);
};