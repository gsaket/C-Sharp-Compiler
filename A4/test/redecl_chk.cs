
using System;

class test3{
	public void Main(string[] args) {
		int x=10;
		int a=0;
		int b=10;
		{
			int x;
			x=a+10;
			b=x*a;
			{
				x=100;
				int a=5;
			}
		}
	}
}
