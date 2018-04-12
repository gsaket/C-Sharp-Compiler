class test 
{
	void Main() 
	{
		int i = 0;
		//char j="charvar";
		char j = 'f';
		int[] a = {6,2,3};
		if (i < 4){
			++a[i];
			if (i > 1){
				--a[i];
			}
		}else {
			a[i] = 1;
		}
		Writeline(a[i]);
	}
}
