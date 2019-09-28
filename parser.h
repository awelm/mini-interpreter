#include <string>
#include <vector>
#include "lexer.h"

#pragma once

using namespace std;

/* GRAMMAR
  statement_list := statement | statement SEMI statement_list
  statement := assignment | conditonal | EMPTY
  conditional := IF OPAREN rvalue CPAREN OBRACE statement_list CBRACE ELSE OBRACE statement_list CBRACE
  assignment := variable EQUAL rvalue
  rvalue := expression [(GREATERTHAN|LESSTHAN|EQUAL EQUAL) expression]
  expression := <divmul>((ADD|SUB)<divmul>)*
  divmul := <factor>((MULT|DIV)<factor>)*
  factor := NUM | SUB factor | (OPAREN expression CPAREN) | variable
  variable := ID
*/

enum NodeType {
  NODE_COMPOUND, //0
  NODE_ADD, //1
  NODE_SUB, //2
  NODE_MULT, //3
  NODE_DIV, //4
  NODE_NEG, //5
  NODE_ASSIGN, //6
  NODE_ID, //7
  NODE_NUM, //8
  NODE_NOOP, //9
  NODE_LESS_THAN, //10
  NODE_GREATER_THAN, //11
  NODE_EQUAL_TO, //12
  NODE_CONDITIONAL //13
};

class ASTNode {
public:
  NodeType nodeType;
  vector<ASTNode*> children;
  int num;
  string id;
  ASTNode(NodeType tt);
};

class Parser {
private:
  Lexer lx;
  Token currToken;
public:
  static const int UNEXPECTED_TOKEN = 17;
  Parser(Lexer l);
  void eat(TokenType t);
  ASTNode* conditional();
  ASTNode* statementList();
  ASTNode* statement();
  ASTNode* rvalue();
  ASTNode* assignment();
  ASTNode* expression();
  ASTNode* divmul();
  ASTNode* factor();
  ASTNode* variable();
};
