using System;

typedef struct
{
  char a;
  int b;
  char c;
  short d;
  double e;
  char name[10];
  char f;
} T;


public class test8{
     public static void Main(){
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
          x.e = 3.141592897932;
          x.f = '*';
          x.name = "abc";
     }
}
