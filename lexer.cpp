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
*/


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
}

bool Lexer::hasNextToken() {
  return nextTokenStart < program.size();
}

pair<Token, string> Lexer::getNextToken() {
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
        pair<Token, string> currTokenPair;
        switch(currChar) {
          case '+':
          currTokenPair = make_pair(ADD, string(1,program[currentIndex]));
          break;
          case '-':
          currTokenPair = make_pair(SUB, string(1,program[currentIndex]));
          break;
          case '*':
          currTokenPair = make_pair(MULT, string(1,program[currentIndex]));
          break;
          case '/':
          currTokenPair = make_pair(DIV, string(1,program[currentIndex]));
          break;
          case ';':
          currTokenPair = make_pair(SEMI, string(1,program[currentIndex]));
          break;
          case '(':
          currTokenPair = make_pair(OPAREN, string(1,program[currentIndex]));
          break;
          case ')':
          currTokenPair = make_pair(CPAREN, string(1,program[currentIndex]));
          break;
        }
        nextTokenStart = currentIndex + 1;
        return currTokenPair;
      } else {
        // Check if string only contains numbers
        string currToken = program.substr(nextTokenStart, currentIndex-nextTokenStart);
        try {
          stoi(currToken);
        } catch(...) {
          throw INVALID_NUMBER;
        }

        nextTokenStart = currentIndex;
        return make_pair(NUM, currToken);
      }
    }

    // continue if you haven't reached a terminal symbol
    else {
      currentIndex++;
    }
  }
}
