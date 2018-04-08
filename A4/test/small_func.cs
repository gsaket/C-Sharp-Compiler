using System;
class test3{
	int Funccall(int a){
		//a=a+1;
		Writeline(a);
		return a+5;
	}
	public void Main(){
		int a;
		a=Funccall(55);
		Writeline(a);
		a=Funccall(66);
		Writeline(a);
	}
}

