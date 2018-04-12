using System;
class test3{
	int Funccall(int a,int b,int c,int lol){
		a  = a+1;
		lol=lol+1;
		return a;
	}

	public void Main(string[] args){
		int a=1,b=2,c=3;
		char p='q';
		int d = Funccall(a,b,c,10);
		Writeline(d);
		//int d = Funccall(a,lol,c,5);
		//int d = Funccall(a,p,c,5);
	}
}

