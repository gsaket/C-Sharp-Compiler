Intermediate Code Specification:

- print statement                   -> 1, print, var
    var will be printed on the standard output

- assignment statement              -> 1, =, a, b
    value of b will be assigned to a

- math-op                          -> 1, MATHOP, a, b, c
    the MATHOP of a and b will be stored in c

- relops                            -> 1, RELOP, res, a, b
    the truth value (0 or 1) will be stored in variable res

- function call                     -> 1, call, func, ret
    the function func will be called and the value returned by it will be 
    stored in ret. arg_num is the number of arguments that the function 
    expects. The arguments must have already been pushed on the stack

- ifgoto                            -> 1, ifgoto, relop, arg1, arg2, l
    if the arg1 relop arg2 is true then the control will jump to label l. 
    otherwise to the next line of the IR. l  should be an integer.
    
- goto                              -> 1, goto, l
    control will jump to label l. l should be an integer.
    
- exit                              -> 1, exit
    exit syscall will be made
    
- function definition               -> 1, function, func
    marks the beginning of the definition of func
    
- return                            -> 1, return, val
    returns the value of val from a function
    
- shift expressions                 -> 1, >>, result, num, count
    num will be shifted count places and the result will be stored in the 
    variable 'result'.
    Similarly for left shift
    
- logical and                       -> 1, &&, result, op1, op2
    
- logical or                        -> 1, ||, result, op1, op2

- C++ not                           -> 1, ~, var
    perform 'not' on var, just like good old C++ :)


- array element                     -> 1, member, var, array_name, offset
    store the value at offset distance from the address of the array 
    array_name into var

- array declaration                 -> 1, array, int, len, name


How to run your code:

$ make
$ bin/codegen test/test1

How to run you AsmbCode:

$ gcc -m32 test1.s
$ ./a.out