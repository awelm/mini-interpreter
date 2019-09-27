#include <string>
#include <vector>
#include "lexer.h"

#pragma once

using namespace std;

/* GRAMMAR
  statement_list := statement | statement SEMI statement_list
  statement := assignment | EMPTY
  assignment := variable ASSIGN expression
  expression := <divmul>((ADD|SUB)<divmul>)*
  divmul := <factor>((MULT|DIV)<factor>)*
  factor := NUM | SUB factor | (OPAREN expression CPAREN) | variable
  variable := ID
*/

class ASTNode {
public:
  TokenType nodeType;
  vector<ASTNode*> children;
  int num;
  string id;
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
  ASTNode* statementList();
  ASTNode* statement();
  ASTNode* assignment();
  ASTNode* expression();
  ASTNode* divmul();
  ASTNode* factor();
  ASTNode* variable();
};
