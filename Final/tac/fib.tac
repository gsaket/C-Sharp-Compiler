0,call,Main,0,NULL
1,exit
2,function,Fact
3,pop,a_2,8
4,==,TP1,a_2,1
5,ifgoto,==,1,TP1,L1
6,goto,L2
7,label,L1
8,return,1
9,label,L2
10,-,TP2,a_2,1
11,param,TP2,1
12,call,Fact,1,TP3
13,*,TP4,a_2,TP3
14,return,TP4
15,function,Main
16,int,a_4
17,=,a_4,5
18,int,x_4
19,param,a_4,1
20,call,Fact,1,TP1
21,=,x_4,TP1
22,print,x_4,int
23,return,NULL
