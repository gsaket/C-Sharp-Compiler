class Rect{
	private int l,b;
	int getarea(){
		return l*b;
	}
	void setLen(int x){
		l=x;
	}
	void setBre(int y){
		b=y;
	}
}
class Hello 
{
	int Main() 
	{
		Rect r=new Rect();
		Rect r1=new Rect();
		r.setLen(5);
		r1.setLen(100);
		r.setBre(6);
		int AR=r.getarea();
		Writeline(AR);
		r1.setBre(200);
		r.setLen(7);
		Writeline(r1.getarea());
		Writeline(r.getarea());
		return 0;
	}
}
