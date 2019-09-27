#include <string>
#include <iostream>
#include "parser.h"

using namespace std;

ASTNode::ASTNode(NodeType tt) {
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

ASTNode* Parser::assignment() {
  ASTNode* varRoot = variable();
  eat(ASSIGN);
  ASTNode* exprRoot = expression();
  ASTNode* assignRoot = new ASTNode(NODE_ASSIGN);
  assignRoot->children.push_back(varRoot);
  assignRoot->children.push_back(exprRoot);
  return assignRoot;
}

ASTNode* Parser::expression() {
  ASTNode* exprRoot = divmul();
  TokenType tt = currToken.tokenType;
  NodeType nt = NODE_NOOP;
  while(tt==ADD || tt==SUB) {
    if(tt==ADD) {
      eat(ADD);
      nt = NODE_ADD;
    }
    else if(tt==SUB) {
      eat(SUB);
      nt = NODE_SUB;
    }
    ASTNode* rightChild = divmul();
    ASTNode* newExprRoot = new ASTNode(nt);
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
  NodeType nt = NODE_NOOP;
  while(tt==MULT || tt==DIV) {
    if(tt==MULT) {
      eat(MULT);
      nt = NODE_MULT;
    }
    else if(tt==DIV) {
      eat(DIV);
      nt = NODE_DIV;
    }

    ASTNode* rightChild = factor();
    ASTNode* newFactorRoot = new ASTNode(nt);
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
    ASTNode* numLeaf = new ASTNode(NODE_NUM);
    numLeaf->num = stoi(t.value);
    return numLeaf;
  } else if(tt == SUB) {
    eat(SUB);
    ASTNode* negRoot = new ASTNode(NODE_NEG);
    negRoot->children.push_back(factor());
    return negRoot;
  } else if(tt == OPAREN){
    eat(OPAREN);
    ASTNode* subExprRoot = expression();
    eat(CPAREN);
    return subExprRoot;
  } else {
    ASTNode* varRoot = variable();
    return varRoot;
  }
}

ASTNode* Parser::variable() {
  Token idToken = currToken;
  eat(ID);
  ASTNode* idLeaf = new ASTNode(NODE_ID);
  idLeaf->id = idToken.value;
  return idLeaf;
}
