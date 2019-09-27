#include <string>

#ifndef LEXER_INCL_GUARD
#define LEXER_INCL_GUARD
#include "lexer.h"
#endif

using namespace std;

class Interpreter {
private:
  Lexer lx;
  Token currToken;
public:
  static const int UNEXPECTED_TOKEN = 17;
  Interpreter(Lexer l);
  void eat(TokenType t);
  int expression();
  int divmul();
  int factor();
};
