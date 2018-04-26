using System;

class test3{
	public void Main(string[] args) {
		char x='q';
		int a=0;
		int b=10;
		switch(x){
			case 'p': a=a+1;break;
			case 'q': a=a+2;a=a*b;
			default : a=a+2;
		}
		Writeline(a);
	}
}
