#include <string>

using namespace std;

enum TokenType {
  NUM,
  ADD,
  SUB,
  MULT,
  DIV,
  SEMI,
  OPAREN,
  CPAREN,
  END,
  EMPTY
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

public:
  static const int INVALID_TOKEN = 15;
  static const int INVALID_NUMBER = 16;

  Lexer(string program);
  bool hasNextToken();
  Token getNextToken();
};
