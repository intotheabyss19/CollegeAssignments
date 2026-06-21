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

public class q14_DiamondPattern {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the number of lines: ");
        int n = scanner.nextInt();
        int mid = n / 2;

        // Top half of the diamond
        for (int i = 0; i <= mid; i++) {
            for (int j = 0; j < mid - i; j++) {
                System.out.print(" ");
            }
            for (int j = 0; j < 2 * i + 1; j++) {
                if (j == 0 || j == 2 * i) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }

        // Bottom half of the diamond
        for (int i = mid - 1; i >= 0; i--) {
            for (int j = 0; j < mid - i; j++) {
                System.out.print(" ");
            }
            for (int j = 0; j < 2 * i + 1; j++) {
                if (j == 0 || j == 2 * i) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            System.out.println();
        }

        scanner.close();
    }
}


