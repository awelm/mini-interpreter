test:
	@g++ -std=c++11 lexer.cpp lexer.h interpreter.cpp interpreter.h tests.cpp && ./a.out
