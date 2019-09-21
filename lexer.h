#include <string>

using namespace std;

enum Token {
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
  pair<Token, string> getNextToken();
};
