/*
XIV. Problem: You are developing an art-inspired programming challenge for an online coding camp. 
The challenge is to create intricate patterns using basic programming concepts. Your task is to 
write a Java program that generates a visually appealing hollow diamond star pattern, which 
will be showcased as part of the camp's digital art exhibition. The pattern should look like this: 
    * 
   * * 
  *   * 
 *     * 
*       *
 *     * 
  *   * 
   * * 
    *
*/

import java.util.Scanner;

public class q14_pattern4 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of lines: ");
        int n = scanner.nextInt();
        int mid = n / 2;

        for (int i = -mid; i <= mid; i++) {
            int row = Math.abs(i);
            System.out.println(" ".repeat(row) + "*" + " ".repeat(n - 2 * row - 2) + (row < mid ? "*" : ""));
        }

        scanner.close();
    }
}

