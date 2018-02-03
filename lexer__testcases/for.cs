using System;

class test3{
	public static void Main(string[] args) {
		int i=6;
		for (;i<= 8 && i>= 6 && i!= 7; i++){
			if (i>=0){
				Console.WriteLine("yes\n");
			}
			else 
			Console.WriteLine("no\n");
		}
		Console.ReadKey();
	}	
}
