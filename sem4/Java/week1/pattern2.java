/*
XII. Problem: Imagine you are developing an educational tool for students learning number 
patterns. Your task is to create a feature that generates a specific numeric pattern, helping 
students visualize number sequences. Write a Java program that outputs the following 
pattern: 
1 
12 
123 
1234 
12345
1234 
123 
12 
1 
*/

import java.util.Scanner;

public class pattern2 {
  public static void main(String[] args) {
    int i = 0, j = 0;
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter n: ");
    int n = sc.nextInt();
    sc.close();

    for(i = 0; i < n; i++){
      for(j = 1; j <= i + 1; j++){
        System.out.print(j);
      }
      System.out.println("");
    }

    for(i = 0; i < n - 1; i++){
      for(j = 1; j < n - i; j++){
        System.out.print(j);
      }
      System.out.println("");
    }
  }
}
