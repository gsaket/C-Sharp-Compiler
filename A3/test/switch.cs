using System;

class test4{
	public void Main(int na, string[] args) {
 	   int wflg = 0, tflg = 0;
 	   int dflg = 0;
 	   char c;
 	   switch(c)
 	   {
 	       case '\'':
		   case '\n' ://'\t':
 	           wflg = 1;
 	           break;
 	       case 't':
 	       case 'T':
 	           tflg = 1;
 	           break;
 	       case 'd':
 	           dflg = 1;
 	           break;
 	   }

		Console.ReadKey();
	}	
}
