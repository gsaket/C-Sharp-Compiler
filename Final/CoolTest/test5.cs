class Program {
    int fact(int y) {
        if (y == 1) {
            return 1;
        }
        return y*fact(y-1) ;
    }
    void Main() {
        int y = 10;
        int x = fact(y);
        Writeline(x);
    }
}
