test:
	@g++ -std=c++11 lexer.cpp lexer.h interpreter.cpp interpreter.h parser.h parser.cpp tests.cpp && ./a.out

clean:
	@rm *.gch a.out mini_interpreter

build:
	@g++ -std=c++11 lexer.cpp lexer.h interpreter.cpp interpreter.h parser.h parser.cpp mini_interpreter.cpp
	@mv a.out mini_interpreter
