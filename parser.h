#include <string>
#include <vector>

#ifndef LEXER_INCL_GUARD
#define LEXER_INCL_GUARD
#include "lexer.h"
#endif

using namespace std;

/* GRAMMAR
  expression := <divmul>((ADD|SUB)<divmul>)*
  divmul := <factor>((MULT|DIV)<factor>)*
  factor := NUM | (OPAREN expression CPAREN)
*/

class ASTNode {
public:
  TokenType nodeType;
  vector<ASTNode*> children;
  int num;
  ASTNode(TokenType tt);
};

class Parser {
private:
  Lexer lx;
  Token currToken;
public:
  static const int UNEXPECTED_TOKEN = 17;
  Parser(Lexer l);
  void eat(TokenType t);
  ASTNode* expression();
  ASTNode* divmul();
  ASTNode* factor();
};
