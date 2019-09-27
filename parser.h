#include <string>
#include <vector>
#include "lexer.h"

#pragma once

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
