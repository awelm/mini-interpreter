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
  else {
    cerr << "Expected token " << tokenType << " but instead received " << this->currToken.tokenType << endl;
    throw UNEXPECTED_TOKEN;
  }
}

ASTNode* Parser::loop() {
  eat(WHILE); eat(OPAREN);
  ASTNode* condition = rvalue();
  eat(CPAREN); eat(OBRACE);
  ASTNode* loopBody = statementList();
  eat(CBRACE);
  ASTNode* loopRoot = new ASTNode(NODE_LOOP);
  loopRoot->children.push_back(condition);
  loopRoot->children.push_back(loopBody);
  return loopRoot;
}

ASTNode* Parser::conditional() {
  eat(IF); eat(OPAREN);
  ASTNode* condition = rvalue();
  eat(CPAREN); eat(OBRACE);
  ASTNode* trueBlock = statementList();
  eat(CBRACE); eat(ELSE); eat(OBRACE);
  ASTNode* falseBlock = statementList();
  eat(CBRACE);
  ASTNode* conditionalRoot = new ASTNode(NODE_CONDITIONAL);
  conditionalRoot->children.push_back(condition);
  conditionalRoot->children.push_back(trueBlock);
  conditionalRoot->children.push_back(falseBlock);
  return conditionalRoot;
}

ASTNode* Parser::statementList() {
  ASTNode* statementList = new ASTNode(NODE_COMPOUND);
  statementList->children.push_back(statement());
  while(this->currToken.tokenType == SEMI) {
    eat(SEMI);
    statementList->children.push_back(statement());
  }
  return statementList;
}

ASTNode* Parser::statement() {
  if(this->currToken.tokenType == ID)
    return assignment();
  else if(this->currToken.tokenType == IF) {
    return conditional();
  } else if(this->currToken.tokenType == WHILE) {
    return loop();
  } else {
    return new ASTNode(NODE_NOOP);
  }
}

ASTNode* Parser::rvalue() {
  ASTNode* expr = expression();
  TokenType tt = this->currToken.tokenType;
  if(tt == LESSTHAN || tt == GREATERTHAN || tt == EQUAL) {
    ASTNode* leftExpr = expr;
    NodeType nt = NODE_NOOP;
    if(tt == LESSTHAN) {
      eat(LESSTHAN);
      nt = NODE_LESS_THAN;
    }
    else if(tt == GREATERTHAN) {
      eat(GREATERTHAN);
      nt = NODE_GREATER_THAN;
    }
    else {
      eat(EQUAL);
      eat(EQUAL);
      nt = NODE_EQUAL_TO;
    }
    ASTNode* rightExpr = expression();
    ASTNode* comparisonRoot = new ASTNode(nt);
    comparisonRoot->children.push_back(leftExpr);
    comparisonRoot->children.push_back(rightExpr);
    return comparisonRoot;
  } else {
    return expr;
  }
}

ASTNode* Parser::assignment() {
  ASTNode* varRoot = variable();
  eat(EQUAL);
  ASTNode* rvalueRoot = rvalue();
  ASTNode* assignRoot = new ASTNode(NODE_ASSIGN);
  assignRoot->children.push_back(varRoot);
  assignRoot->children.push_back(rvalueRoot);
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
