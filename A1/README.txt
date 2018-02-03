The source .y and .l files are in the "src" directory.

The intermediate .tab.c, .tab.h and lex.yy.c files are created in the "build" directory.

The test cases are in the "test" directory.

The binary for the lexer is in the "bin" directory.

Instructions to build (assuming you are outside the asgn1 folder):

$ cd asgn1
$ make

Instructions to run the lexer:

$ bin/lexer test/test1.cs
