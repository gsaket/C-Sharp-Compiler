using System;

struct T
{
  char a;
  int b;
  char c;
  //char name[10];
  //arrays not included as struct fields in grammar
  char f;
}


public class test8{
     public void Main(){
          test8 tmp=new test8();
          T k;
          tmp.f(k);
          Console.ReadKey();
     }
     void f (T x)
     {
          x.a = 'a';
          x.b = 47114711;
          x.c = 'c';
          x.d = 1234;
          x.e = 3141592897932;
          x.f = '*';
          x.name = "abc";
     }
}
