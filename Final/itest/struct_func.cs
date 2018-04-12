using System;

class IAMROOT{
	int hey;
	void IDK(){
		hey=hey+1;
	}
}
class Hello 
{
	int uppar;
	class T
	{
		char a;
		int b;
		//char c;
		//short d;
		//char f;
	};
	int neeche;
	void f ()
	{
		T x = new T();
		x.a = 'a';
		x.b = 4711;
		//x.c = 'c';
		//x.d = 1234;
		//x.f = '*';
	}
	void Main() 
	{
		T k=new T();
		//f();
		k.b=85;
		IAMROOT lol=new IAMROOT();
		lol.hey = k.b*1000;
		lol.IDK();
		Writeline(lol.hey);
	}
}
