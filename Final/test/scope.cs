
using System;

class test3{
	public void Main(string[] args) {
		int x=10;
		int a=0;
		int b=10;
		int z=15;
		{
			int z=10;
			z = z+1;
			{
				int z=12;
				z = z+2;
			}
		}
	}
}
