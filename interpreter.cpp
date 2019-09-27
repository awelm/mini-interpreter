#include <string>
#include <iostream>
#include "interpreter.h"

using namespace std;

Interpreter::Interpreter(Parser p): p(p) {
}

void Interpreter::interpret() {
  // Assuming start symbol is 'statement_list'
  visit(p.statementList());
}

int Interpreter::visit(ASTNode* n) {
  switch(n->nodeType) {
    case NODE_COMPOUND:
    return visitCompound(n);
    case NODE_NUM:
    return visitNum(n);
    break;
    case NODE_NEG:
    return visitUnaryOperator(n);
    break;
    case NODE_ADD:
    case NODE_SUB:
    case NODE_MULT:
    case NODE_DIV:
    return visitBinaryOperator(n);
    break;
    case NODE_ASSIGN:
    return visitAssignOperator(n);
    break;
    case NODE_NOOP:
    break;
    case NODE_ID:
    return visitVar(n);
    break;
    default:
    throw UNEXPECTED_TOKEN;
    break;
  }
}

// visit and evaluate child nodes from left to right. Return value isnt used
int Interpreter::visitCompound(ASTNode* n) {
  for(int child = 0; child < n->children.size(); child++) {
    visit(n->children[child]);
  }
  return 0;
}

int Interpreter::visitBinaryOperator(ASTNode* n) {
  int leftVal = visit(n->children[0]);
  int rightVal = visit(n->children[1]);
  switch(n->nodeType) {
    case NODE_ADD:
    return leftVal + rightVal;
    break;
    case NODE_SUB:
    return leftVal - rightVal;
    break;
    case NODE_MULT:
    return leftVal * rightVal;
    break;
    case NODE_DIV:
    return leftVal / rightVal;
    break;
    default:
    throw UNEXPECTED_TOKEN;
    break;
  }
}

int Interpreter::visitUnaryOperator(ASTNode* n) {
  int childVal = visit(n->children[0]);
  switch(n->nodeType) {
    case NODE_NEG:
    return -1 * childVal;
    default:
    throw UNEXPECTED_TOKEN;
    break;
  }
}

int Interpreter::visitAssignOperator(ASTNode* n) {
  string varName = n->children[0]->id;
  int rightVal = visit(n->children[1]);
  symbolTable[varName] = rightVal;
  return rightVal;
}

int Interpreter::visitNum(ASTNode* n) {
  return n->num;
}

int Interpreter::visitVar(ASTNode* n) {
  string varName = n->id;
  if(symbolTable.find(varName) == symbolTable.end())
  throw UNKNOWN_SYMBOL;
  return symbolTable[varName];
}

int Interpreter::getRuntimeValue(string variable) {
  if(symbolTable.find(variable) == symbolTable.end())
    throw UNKNOWN_SYMBOL;
  return symbolTable[variable];
}
