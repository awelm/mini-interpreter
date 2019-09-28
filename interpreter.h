#include <string>
#include "parser.h"
#include "lexer.h"
#include <unordered_map>

#pragma once

using namespace std;

class Interpreter {
private:
  Parser p;
  unordered_map<string, int> symbolTable;
  int visit(ASTNode* n);
  int visitCompound(ASTNode* n);
  int visitConditional(ASTNode* n);
  int visitUnaryOperator(ASTNode* n);
  int visitBinaryOperator(ASTNode* n);
  int visitAssignOperator(ASTNode* n);
  int visitNum(ASTNode* n);
  int visitVar(ASTNode* n);
public:
  static const int UNEXPECTED_TOKEN = 17;
  static const int UNKNOWN_SYMBOL = 18;
  Interpreter(Parser p);
  void interpret();
  int getRuntimeValue(string variable);
};
