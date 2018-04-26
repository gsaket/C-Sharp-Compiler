class Rect{
	private int l,b;
	int getarea(){
		return l*b;
	}
	private void setLen(int x){
		l=x;
	}
	void getLen(){
		return l;
	}
	void getBreadth(){
		return b;
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
	int Fact(int a){
		if(a == 1){
			return 1;
		}
		return a*Fact(a-1);
	}
	int Main() 
	{
		Rect r=new Rect();
		for(int i=1; i<=3; i++){
			r.setLB(Fact(i),Fact(i+1));
			Writeline(r.getLen());
			Writeline(r.getBreadth());
			Writeline(r.getarea());
		}
		return 0;
	}
}

