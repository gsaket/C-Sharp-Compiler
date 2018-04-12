class test3{
	char Funccall(int a,char ch){
		//a=a+1;
		Writeline(a);
		if(a == 5){
			ch = 'a';
		}
		else{
			ch = 'b';
		}
		return ch;
	}
	public void Main(){
		//int a;
		//Readline(a);
		//Writeline(a);
		//a=Funccall(55);
		//Writeline(a);
		//a=Funccall(66);
		//Writeline(a);
		Writeline("Let's print a string!!");
		char b;
		Readline(b);
		Writeline(b);
		char t = Funccall(5,b);
		Writeline(t);
	}
}

