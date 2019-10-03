#include "interpreter.h"
#include "parser.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2) {
        cerr << "Wrong number of arguments were passed. Expected only 1 argument (file path)" << endl;
        return 1;
    }
    string programPath(argv[1]);
    if(programPath.find(".minlang") == string::npos) {
        cerr << "Program should end with a .minlang suffix" << endl;
        return 1;
    }
    ifstream t(programPath);
    string program((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());
    Lexer lx(program);
    Parser p(lx);
    Interpreter i(p);
    i.interpret();
    return 0;
}