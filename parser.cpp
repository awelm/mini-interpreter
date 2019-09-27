#include <string>
#include <iostream>
#include "parser.h"

using namespace std;

ASTNode::ASTNode(TokenType tt) {
  this->nodeType = tt;
}

Parser::Parser(Lexer l): lx(l) {
  currToken = lx.getNextToken();
}

void Parser::eat(TokenType tokenType) {
  if(this->currToken.tokenType == tokenType) {
    this->currToken = lx.getNextToken();
  }
  else
  throw UNEXPECTED_TOKEN;
}

ASTNode* Parser::expression() {
  ASTNode* exprRoot = divmul();
  TokenType tt = currToken.tokenType;
  while(tt==ADD || tt==SUB) {
    if(tt==ADD)
      eat(ADD);
    else if(tt==SUB)
      eat(SUB);
    ASTNode* rightChild = divmul();
    ASTNode* newExprRoot = new ASTNode(tt);
    newExprRoot->children.push_back(exprRoot);
    newExprRoot->children.push_back(rightChild);
    exprRoot = newExprRoot;
    tt = currToken.tokenType;
  }
  return exprRoot;
}

ASTNode* Parser::divmul() {
  ASTNode* factorRoot = factor();
  TokenType tt = currToken.tokenType;
  while(tt==MULT || tt==DIV) {
    if(tt==MULT)
      eat(MULT);
    else if(tt==DIV)
      eat(DIV);

    ASTNode* rightChild = factor();
    ASTNode* newFactorRoot = new ASTNode(tt);
    newFactorRoot->children.push_back(factorRoot);
    newFactorRoot->children.push_back(rightChild);
    factorRoot = newFactorRoot;
    tt = currToken.tokenType;
  }
  return factorRoot;
}

ASTNode* Parser::factor() {
  Token t = currToken;
  TokenType tt = currToken.tokenType;
  if(tt == NUM) {
    eat(NUM);
    ASTNode* numLeaf = new ASTNode(NUM);
    numLeaf->num = stoi(t.value);
    return numLeaf;
  } else if(tt == NEG) {
    eat(NEG);
    ASTNode* negRoot = new ASTNode(NEG);
    negRoot->children.push_back(factor());
    return negRoot;
  } else {
    eat(OPAREN);
    ASTNode* subExprRoot = expression();
    eat(CPAREN);
    return subExprRoot;
  }
}
