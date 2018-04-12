using System;
class test3{
	int Fact(int a){
		if(a == 1){
			return 1;
		}
		return a*Fact(a-1);
	}
	public void Main(){
		int a = 5;
		int x = Fact(a);
		Writeline(x);
		//a=Funccall(66);
		//Writeline(a);
	}
}

