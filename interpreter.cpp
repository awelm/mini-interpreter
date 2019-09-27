#include <string>
#include <iostream>
#include "interpreter.h"

using namespace std;

Interpreter::Interpreter(Parser p): p(p) {
}

int Interpreter::interpret() {
  // Assuming start symbol is 'expression'
  return visit(p.expression());
}

int Interpreter::visit(ASTNode* n) {
  switch(n->nodeType) {
    case NUM:
      return visitNum(n);
      break;
    case NEG:
      return visitUnaryOperator(n);
      break;
    case ADD:
    case SUB:
    case MULT:
    case DIV:
      return visitBinaryOperator(n);
      break;
    default:
      throw UNEXPECTED_TOKEN;
      break;
  }
}

int Interpreter::visitUnaryOperator(ASTNode* n) {
  int childVal = visit(n->children[0]);
  switch(n->nodeType) {
    case NEG:
      return -1 * childVal;
    default:
      throw UNEXPECTED_TOKEN;
      break;
  }
}

int Interpreter::visitBinaryOperator(ASTNode* n) {
  int leftVal = visit(n->children[0]);
  int rightVal = visit(n->children[1]);
  switch(n->nodeType) {
    case ADD:
      return leftVal + rightVal;
      break;
    case SUB:
      return leftVal - rightVal;
      break;
    case MULT:
      return leftVal * rightVal;
      break;
    case DIV:
      return leftVal / rightVal;
      break;
    default:
      throw UNEXPECTED_TOKEN;
      break;
  }
}

int Interpreter::visitNum(ASTNode* n) {
  return n->num;
}
