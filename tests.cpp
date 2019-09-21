#include "lexer.h"
#include <iostream>
#include <vector>

void lexerTests() {
  Lexer lx("123+342;");
  vector<pair<Token, string> > output;
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(NUM, string("123")));
  assert(output[1] == make_pair(ADD, string("+")));
  assert(output[2] == make_pair(NUM, string("342")));

  lx = Lexer("123456;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(NUM, string("123456")));

  // test overflow case
  lx = Lexer("5000000000;");
  bool exceptionThrown = false;
  try {
    lx.getNextToken();
  } catch (int e) {
    if(e == Lexer::INVALID_NUMBER)
      exceptionThrown = true;
  }
  assert(exceptionThrown);

  lx = Lexer("1+2-3*4;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(NUM, string("1")));
  assert(output[1] == make_pair(ADD, string("+")));
  assert(output[2] == make_pair(NUM, string("2")));
  assert(output[3] == make_pair(SUB, string("-")));
  assert(output[4] == make_pair(NUM, string("3")));
  assert(output[5] == make_pair(MULT, string("*")));
  assert(output[6] == make_pair(NUM, string("4")));

  lx = Lexer("(4/2)+1;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(OPAREN, string("(")));
  assert(output[1] == make_pair(NUM, string("4")));
  assert(output[2] == make_pair(DIV, string("/")));
  assert(output[3] == make_pair(NUM, string("2")));
  assert(output[4] == make_pair(CPAREN, string(")")));
  assert(output[5] == make_pair(ADD, string("+")));
  assert(output[6] == make_pair(NUM, string("1")));

  // whitespace tests
  lx = Lexer("4  + 1;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(NUM, string("4")));
  assert(output[1] == make_pair(ADD, string("+")));
  assert(output[2] == make_pair(NUM, string("1")));

  lx = Lexer("   123456  ;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == make_pair(NUM, string("123456")));
}

int main() {
  lexerTests();
  cout << "All tests passed" << endl;
  return 0;
}
