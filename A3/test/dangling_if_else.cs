using System;

public class test7{
     public void main(){
          int i = 0;
          int [] a=new int[]{1,2,3};
          if (i<=3)
               ++a[i];
          if (i>=2)
               --a[i];
          else
               a[i] = 1;
          Console.ReadKey();
     }
}
