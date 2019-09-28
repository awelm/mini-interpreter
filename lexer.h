#include <string>
#include <unordered_map>

#pragma once

using namespace std;

enum TokenType {
  NUM, //0
  ADD, //1
  SUB, //2
  MULT, //3
  DIV, //4
  SEMI, //5
  OPAREN, //6
  CPAREN, //7
  END, //8
  ID, //9
  EQUAL, //10
  LESSTHAN, //11
  GREATERTHAN, //12
  IF, //13
  ELSE, //14
  OBRACE, //15
  CBRACE, //16
  WHILE, //17
  EMPTY //18
};

struct Token {
  Token();
  Token(TokenType tt, string t);
  TokenType tokenType;
  string value;
};

bool operator==(const Token& lhs, const Token& rhs);

class Lexer {
private:
  string program;
  int nextTokenStart;
  bool isTerminal(char c);
  Token prevToken;
  Token getMultiCharToken(string currTokenValue);

public:
  static const int INVALID_TOKEN = 15;
  static const int INVALID_NUMBER = 16;

  Lexer(string program);
  bool hasNextToken();
  Token getNextToken();
  Token peek();
};
