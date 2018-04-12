class Program {
    int d ;
    int l = 6, m = d, p;
    int fact(int y) {
        if (y == 1) {
            return 1;
        }
        return y*fact(y-1) ;
    }
    int doublefact(int x) {
        return d*fact(x);
    }
    void Main() {
        d=2;
        int y = 5;
        int x = doublefact(y);
        Writeline(x);
    }
}
