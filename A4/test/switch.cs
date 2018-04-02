using System;

class test3{
	public void Main(string[] args) {
		int x=10;
		int a=0;
		int b=10;
		switch(x){
			case 1: a=a+1;break;
			case 10: a=a+2;a=a*b;
			default : a=a+2;
		}
	}
}
