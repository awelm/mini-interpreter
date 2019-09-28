#include <iostream>
#include <vector>
#include <string>

#include "lexer.h"

using namespace std;

/*
Supported operations:
add: 123+4
sub: 4-2
multiply: 1*1
divide: 4/2
parentheses: (4+1)
negative operator: 3 + -2
variable: x = 4 + 2 - y
comparision: x = a < 4, y = a > b, z = b==x
conditional: if(a<b) { x=1;} else {x=2;};
loop: while(a<10) {a++;};
*/

const unordered_map<string, Token> RESERVED_KEYWORDS = {
    {"if", Token(IF, "if")},
    {"else", Token(ELSE, "else")},
    {"while", Token(WHILE, "while")}
};

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
  if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c==';' || c=='=' || c=='<' || c=='>' || c=='{' || c=='}')
  return true;
  else
  return false;
}

Token Lexer::getMultiCharToken(string currTokenValue) {
  int alphaCount = 0;
  int digitCount = 0;
  for(int x=0; x<currTokenValue.size(); x++) {
    if(isalpha(currTokenValue[x]))
      alphaCount++;
    else if(isdigit(currTokenValue[x]))
      digitCount++;
    else {
      cerr << "Unable to parse token " << currTokenValue << endl;
      throw INVALID_TOKEN;
    }
  }
  if(digitCount == currTokenValue.size())
    return Token(NUM, currTokenValue);
  else {
    // treat language keywords specially
    if(RESERVED_KEYWORDS.find(currTokenValue) != RESERVED_KEYWORDS.end())
      return RESERVED_KEYWORDS.find(currTokenValue)->second;
    else
      return Token(ID, currTokenValue);
  }
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
          currToken = Token(SUB, string(1,program[currentIndex]));
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
          case '=':
          currToken = Token(EQUAL, string(1,program[currentIndex]));
          break;
          case '<':
          currToken = Token(LESSTHAN, string(1,program[currentIndex]));
          break;
          case '>':
          currToken = Token(GREATERTHAN, string(1,program[currentIndex]));
          break;
          case '{':
          currToken = Token(OBRACE, string(1,program[currentIndex]));
          break;
          case '}':
          currToken = Token(CBRACE, string(1,program[currentIndex]));
          break;
        }
        nextTokenStart = currentIndex + 1;
        prevToken = currToken;
        return currToken;
      } else {
        string currTokenValue = program.substr(nextTokenStart, currentIndex-nextTokenStart);
        Token extractedToken = getMultiCharToken(currTokenValue);

        // Token validation
        switch(extractedToken.tokenType) {
          case NUM:
          try {
            stoi(currTokenValue);
          } catch(...) {
            throw INVALID_NUMBER;
          }
          break;
          default:
          break;
        }

        nextTokenStart = currentIndex;
        prevToken = extractedToken;
        return extractedToken;
      }
    }

    // continue if you haven't reached a terminal symbol
    else {
      currentIndex++;
    }
  }

  return Token(EMPTY, "");
}

Token Lexer::peek() {
  // save all state, call getNextToken, and then restore state
  int savedNextTokenStart = nextTokenStart;
  Token savedPrevToken = prevToken;
  Token peekedToken = getNextToken();
  nextTokenStart = savedNextTokenStart;
  prevToken = savedPrevToken;
  return peekedToken;
}
