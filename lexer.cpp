#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"

using namespace std;

/*
Supported operations:
add: 123+4;
sub: 4-2;
multiply: 1*1;
divide: 4/2;
parentheses: (4+1);
negative operator: 3 + -2;
*/

Token::Token() {
  this->tokenType = EMPTY;
}

Token::Token(TokenType tt, string val) {
  this->tokenType = tt;
  this->value = val;
}

bool operator==(const Token& lhs, const Token& rhs) {
    return lhs.tokenType == rhs.tokenType && lhs.value == rhs.value;
}

bool Lexer::isTerminal(char c) {
  if (isspace(c))
    return true;
  if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c==';')
    return true;
  else
    return false;
}

Lexer::Lexer(string program) {
  nextTokenStart = 0;
  this->program = program;
  prevToken = Token();
}

bool Lexer::hasNextToken() {
  return nextTokenStart < program.size();
}

Token Lexer::getNextToken() {
  int currentIndex = nextTokenStart;

  while(currentIndex < program.size()) {
    char currChar = program[currentIndex];

    // terminate matching process once you reach a terminal symbol
    if(isTerminal(currChar)) {
      // If current terminal is only one character long
      if(currentIndex == nextTokenStart) {
        if(isspace(currChar)) {
          // skip whitespace tokens
          nextTokenStart++;
          currentIndex++;
          continue;
        }
        Token currToken;
        switch(currChar) {
          case '+':
          currToken = Token(ADD, string(1,program[currentIndex]));
          break;
          case '-':
            if(prevToken.tokenType == CPAREN || prevToken.tokenType == NUM)
              currToken = Token(SUB, string(1,program[currentIndex]));
            else
              currToken = Token(NEG, string(1,program[currentIndex]));
          break;
          case '*':
          currToken = Token(MULT, string(1,program[currentIndex]));
          break;
          case '/':
          currToken = Token(DIV, string(1,program[currentIndex]));
          break;
          case ';':
          currToken = Token(SEMI, string(1,program[currentIndex]));
          break;
          case '(':
          currToken = Token(OPAREN, string(1,program[currentIndex]));
          break;
          case ')':
          currToken = Token(CPAREN, string(1,program[currentIndex]));
          break;
        }
        nextTokenStart = currentIndex + 1;
        prevToken = currToken;
        return currToken;
      } else {
        // Check if string only contains numbers
        string currTokenValue = program.substr(nextTokenStart, currentIndex-nextTokenStart);
        try {
          stoi(currTokenValue);
        } catch(...) {
          throw INVALID_NUMBER;
        }

        nextTokenStart = currentIndex;
        prevToken = Token(NUM, currTokenValue);
        return prevToken;
      }
    }

    // continue if you haven't reached a terminal symbol
    else {
      currentIndex++;
    }
  }

  return Token(EMPTY, "");
}
