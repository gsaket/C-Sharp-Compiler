The source .y and .l files are in the "src" directory.

The intermediate .tab.c, .tab.h and lex.yy.c files are created in the "build" directory.

The test cases are in the "test" and "itest" directories.

The binary for the IR generator is in the "bin" directory.

Instructions to build (assuming you are outside the A4 folder):

$ cd A4
$ make

Instructions to run the IR generator:

$ bin/sharpie itest/test1.cs
