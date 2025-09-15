/*
Problem: You are teaching a course on advanced Java techniques, and you want to show the power of bitwise operators. 
Write a Java program that swaps the values of two given numbers using bitwise operators, 
demonstrating a non-traditional method of swapping values without using a temporary variable.
*/

import java.util.Scanner;

class Swapper {
    public static int[] swapperNum(int a, int b) {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        
        return new int[]{a, b};
    }
}

class SwapNum {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        System.out.print("Enter num1: ");
        int a = sc.nextInt();
        
        System.out.print("Enter num2: ");
        int b = sc.nextInt();
        
        System.out.println("Value of a is " + a);
        System.out.println("Value of b is " + b);
        
        int[] swappedValues = Swapper.swapperNum(a, b);
        
        a = swappedValues[0];
        b = swappedValues[1];
        
        System.out.println("Value of a after swapping is " + a);
        System.out.println("Value of b after swapping is " + b);
    }
}
