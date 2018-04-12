using System;
class Hello 
{
    void Main() 
    {
	int wflg = 0, tflg = 0;
	int dflg = 0;
	char c='d';
	switch(c)
	{
	    case 'w': ;
	    case 'W':
		wflg = 1;
		break;
	    case 't': ; // terminator req for empty statement
	    case 'T':
		tflg = 1;
		break;
	    case 'd':
		dflg = 1;
		//break;
	}
	Writeline(dflg);
	return 0;
    }
}
