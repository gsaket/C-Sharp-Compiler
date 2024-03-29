###############################################################################
CBlunt - A C# Compiler written in C++
Authors: Akshat Jindal, Ginuga Saketh, Arjun Sinha
Group 12
###############################################################################

# Language Features:
    a.  Data Types - int, one dimensional arrays of int, char
    b.  Operators
            int:
                - Unary -> !,-,~,+
                - Relational ->  <, >, ==, !=
                - Arithmetic -> +,-,/,%
                - Bitwise -> <<,>>,&,|,^
                - Logical ops -> &&,||
                - Assignment -> = 
            bool (realized as int 0 and 1):
                - Unary-> !
                - Logical -> &&,||
                - Assignment -> =
            Arrays:
            	- Same as int

    c.  Loops -> for, while
    d.  Selection Statements -> if, if-else, switch case

    e.  Arrays -> 1-D arrays of types - {int}
        - Format allowed for initialization, int[] a = {1,2,3,4};
    f.  Classes
        - Data member, member functions, access modifiers
    g.  Structs are supported
    h.  Functions
        - Allowed return types -> int,char,bool
        - Allowed argument types -> int,char,bool
    i.  Scoping
    	- Implemented as a tree of symbol tables
    j.  boolean expressions realized as integer 0 and 1 wit relational operators
    k.	pre increment/decrement
    l.  read from stdin(only int)
    m.  Multiple Declarations and Sequential Assignments
        - Multiple Declarations  -> int a,b,c=3;
        - Sequential Assignments -> a=b=c=3;
    n.  break,continue statements

NOTE:
Braces required in blocks (even if single statement) for if, else, while, for etc.
Otherwise scope might be misunterstood by the compiler


###############################################################################

# Intermediate Code Specification
    The generated IR code begins with a call to main function followed by a 
    call to exit. So, the input program must have a main and only one main 
    function in it. 

    - print statement                   -> 1, print, var
        var will be printed on the standard output
    
    - assignment statement              -> 1, =, a, b
        value of b will be assigned to a
    
    - addition                          -> 1, +, a, b, c
        the sum of a and b will be stored in c
    
    - subtraction                       -> 1, -, a, b, c
        b-a will be stored in c
    
    - multiplication                    -> 1, *, a, b, c
        the product of a and b will be stored in c
    
    - division                          -> 1, /, a, b, c
        the value of a/b will be stored in c
    
    - modulo                            -> 1, %, a, b, c
        the value of a%b will be stored in c
    
    - relops                            -> 1, <, res, a, b
        the truth value (0 or 1) will be stored in variable res

    - function parameters               -> 1, param, val
        the function parameter val will be pushed on the stack. This ir will 
        be followed by a function call or another param ir
    
    - function call                     -> 1, call, func, arg_num, ret
        the function func will be called and the value returned by it will be 
        stored in ret. arg_num is the number of arguments that the function 
        expects. The arguments must have already been pushed on the stack
    
    - pop                               -> 1, pop, var
        store the value on stack into var, to be used as function parameter value
        
    - label                             -> 1, label, l
        a label is introduced
    
    - ifgoto                            -> 1, ifgoto, relop, arg1, arg2, l
        if the arg1 relop arg2 is true then the control will jump to label l. 
        otherwise to the next line of the IR
    
    - goto                              -> 1, goto, l
        control will jump to label l
    
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
    
    - bitwise not                       -> 1, ~, var
        perform bitwise not on var
    
    - logical not                       -> 1, !, var
        perform logical not on var

    - array element                     -> 1, member, var, array_name, offset
        store the value at offset distance from the address of the array 
        array_name into var

    - declaration                       -> 1, int, var

    - array declaration                 -> 1, array, int, len, name

How to run:
1) make
2) Set up test directory in bin/csharp
3) $$ bin/csharp filename
4  $$ ./a.out
