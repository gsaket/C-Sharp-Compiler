0,call,Main,0,NULL
1,exit
2,function,Main
3,pop,args_2,8
4,char,x_2
5,=,x_2,'q'
6,int,a_2
7,=,a_2,0
8,int,b_2
9,=,b_2,10
10,goto,L1
11,label,L3
12,+,TP1,a_2,1
13,=,a_2,TP1
14,goto,L2
15,label,L4
16,+,TP2,a_2,2
17,=,a_2,TP2
18,*,TP3,a_2,b_2
19,=,a_2,TP3
20,label,L5
21,+,TP4,a_2,2
22,=,a_2,TP4
23,goto,L2
24,label,L1
25,ifgoto,==,'p',x_2,L3
26,ifgoto,==,'q',x_2,L4
27,goto,L5
28,label,L2
29,print,a_2,int
30,return,NULL
