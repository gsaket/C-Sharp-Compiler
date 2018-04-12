using System;

class test3{
	public void Main() {
		int x=10;
		int a=0;
		int b=20;
		while(x>0){
			a=b*10;
			b=b+5;
			x=x-1;
			Writeline(a);
			//Writeline(b);
		}
	}
}
