#include <string>
#include "lexer.h"

using namespace std;

/* GRAMMAR
  expression := <divmul>((ADD|SUB)<divmul>)*
  divmul := <factor>((MULT|DIV)<factor>)*
  factor := NUM | (OPAREN expression CPAREN)
*/

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
