class test3{
	char Funccall(int a,char ch){
		//a=a+1;
		if(ch == 'b'){
			ch = 'a';
			Writeline(a);
		}
		else{
			ch = 'b';
			Writeline(a+100);
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
		//char b;
		//Readline(b);
		//Writeline(b);
		char t = Funccall(5,'b');
		//Writeline(t);
	}
}

