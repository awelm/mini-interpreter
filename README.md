# mini-interpreter

I built this simple interpreter to understand how interpreters and compilers really work under the hood! The mini-language currently supports variables (only integers), conditionals, loops, and print statements. This project is currently in active development.

Here is an example program that computes 1+2+3+...+10:
```
  counter = 1;
  total = 0;
  maxSummand = 10;
  while(counter < maxSummand+1) {
    total = total + counter;
    counter = counter + 1;
  }
  print total
```

## Test
Run `make test` to run the various lexer and interpreter tests that I have written. You can also run `make build` and then run a test program I wrote to print out all positive even numbers <= 50 using `./mini_interpreter test_programs/print_evens.minlang`

## Run
Run `make build` to build the interpreter binary. Then run `./mini_interpreter <path/to/program/programName.minlang>` to run your minlang program.
