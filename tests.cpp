#include "interpreter.h"
#include <iostream>
#include <vector>

void lexerTests() {
  Lexer lx("123+342;");
  vector<Token> output;
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == Token(NUM, string("123")));
  assert(output[1] == Token(ADD, string("+")));
  assert(output[2] == Token(NUM, string("342")));

  lx = Lexer("123456;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == Token(NUM, string("123456")));

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
  assert(output[0] == Token(NUM, string("1")));
  assert(output[1] == Token(ADD, string("+")));
  assert(output[2] == Token(NUM, string("2")));
  assert(output[3] == Token(SUB, string("-")));
  assert(output[4] == Token(NUM, string("3")));
  assert(output[5] == Token(MULT, string("*")));
  assert(output[6] == Token(NUM, string("4")));

  lx = Lexer("(4/2)+1;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == Token(OPAREN, string("(")));
  assert(output[1] == Token(NUM, string("4")));
  assert(output[2] == Token(DIV, string("/")));
  assert(output[3] == Token(NUM, string("2")));
  assert(output[4] == Token(CPAREN, string(")")));
  assert(output[5] == Token(ADD, string("+")));
  assert(output[6] == Token(NUM, string("1")));

  // whitespace tests
  lx = Lexer("4  + 1;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == Token(NUM, string("4")));
  assert(output[1] == Token(ADD, string("+")));
  assert(output[2] == Token(NUM, string("1")));

  lx = Lexer("   123456  ;");
  output.clear();
  while(lx.hasNextToken())
    output.push_back(lx.getNextToken());
  assert(output[0] == Token(NUM, string("123456")));
}

void interpreterTests() {
  Lexer lx("123+342;");
  assert(Interpreter(lx).expression() == 465);

  lx = Lexer("4  - 12;");
  assert(Interpreter(lx).expression() == -8);

  lx = Lexer("4 + 3 * 8;");
  assert(Interpreter(lx).expression() == 28);

  lx = Lexer("(4 + 3) * 8;");
  assert(Interpreter(lx).expression() == 56);

  lx = Lexer("(((4)));");
  assert(Interpreter(lx).expression() == 4);

  lx = Lexer("(80-10)/7 + 4;");
  assert(Interpreter(lx).expression() == 14);

  // Test invalid expressions 
  lx = Lexer("1+;");
  bool exceptionThrown = false;
  try {
    Interpreter(lx).expression();
  } catch (int e) {
    if(e == Interpreter::UNEXPECTED_TOKEN)
      exceptionThrown = true;
  }
  assert(exceptionThrown);

  lx = Lexer("1++3;");
  exceptionThrown = false;
  try {
    Interpreter(lx).expression();
  } catch (int e) {
    if(e == Interpreter::UNEXPECTED_TOKEN)
      exceptionThrown = true;
  }
  assert(exceptionThrown);
}


int main() {
  lexerTests();
  interpreterTests();
  cout << "All tests passed" << endl;
  return 0;
}
