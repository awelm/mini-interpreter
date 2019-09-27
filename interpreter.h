#include <string>
#include "parser.h"
#include "lexer.h"

#pragma once

using namespace std;

class Interpreter {
private:
  Parser p;
  int visit(ASTNode* n);
  int visitOperator(ASTNode* n);
  int visitNum(ASTNode* n);
public:
  static const int UNEXPECTED_TOKEN = 17;
  Interpreter(Parser p);
  int interpret();
};
