#include <string>
#include <iostream>
#include "interpreter.h"

using namespace std;

Interpreter::Interpreter(Lexer l): lx(l) {
  currToken = lx.getNextToken();
}

void Interpreter::eat(TokenType tokenType) {
  if(this->currToken.tokenType == tokenType) {
    this->currToken = lx.getNextToken();
  }
  else
    throw UNEXPECTED_TOKEN;
}

int Interpreter::expression() {
  int totalSum = divmul();
  while(currToken.tokenType==ADD || currToken.tokenType==SUB) {
      if(currToken.tokenType==ADD) {
        eat(ADD);
        totalSum += divmul();
      }
      else {
        eat(SUB);
        totalSum -= divmul();
      }
  }
  return totalSum;
}

int Interpreter::divmul() {
  int totalProd = factor();
  while(currToken.tokenType==MULT || currToken.tokenType==DIV) {
      if(currToken.tokenType==MULT) {
        eat(MULT);
        totalProd *= divmul();
      }
      else {
        eat(DIV);
        totalProd /= divmul();
      }
  }
  return totalProd;
}

int Interpreter::factor() {
  Token t = currToken;
  if(t.tokenType == NUM) {
    eat(NUM);
    return stoi(t.value);
  } else {
    eat(OPAREN);
    int expressionVal = expression();
    eat(CPAREN);
    return expressionVal;
  }
}
