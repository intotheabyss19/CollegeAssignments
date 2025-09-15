/*
XI. Problem: You  are  working  on  a  graphical  interface  for  a  star  pattern  generator  in  a 
children's  learning  application.  This  feature  needs  to  display  various  star  patterns  to 
engage young users. Write a Java program that outputs the following star pattern: 
       * 
      *** 
     ***** 
    ******* 
   *********
*/
import java.util.Scanner;

class pattern1{
   public static void main(String[] args){
      int i = 0, j = 0, k = 0;
      Scanner sc = new Scanner(System.in);
      System.out.print("Enter n: ");
      int n = sc.nextInt();

      for(i = 0; i < n; i++){
        for(j = 0; j < n - i; j++){
          System.out.print(" ");
        }
        for(k = 0; k <= i*2; k+=1){
          System.out.print("*");
        }
        System.out.println("");
      }
      sc.close();
      Runtime r = Runtime.getRuntime();
      System.out.println(r.freeMemory());
   }
}
