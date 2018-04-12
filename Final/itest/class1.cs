class Rect{
	private int l,b;
	int getarea(){
		return l*b;
	}
	private void setLen(int x){
		l=x;
	}
	private void setBre(int y){
		b=y;
	}
	void setLB(int x, int y){
		setLen(x);
		setBre(y);
	}
}
class Hello 
{
	int Main() 
	{
		Rect r=new Rect();
		r.setLB(5,6);
		Writeline(r.getarea());
		return 0;
	}
}
