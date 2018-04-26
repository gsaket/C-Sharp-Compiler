class test3{
	public void Main() {
		int x=10;
		int a=1;
		int b=10;
		Writeline(x);
		{
			int x;
			x=20;
			b=x*a;
			Writeline(x);
			{
				x=100;
				int a=5;
				Writeline(x);
			}
			Writeline(x);
		}
		Writeline(x);
	}
}
