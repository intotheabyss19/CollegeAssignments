/*
XIII. Problem: You are tasked with creating a fun and interactive feature for a math and art integration 
project in a children's educational app. The goal is to generate an engaging pattern that mixes 
numbers and stars to captivate young learners. Write a Java program that outputs the following 
mixed pattern: 
1 
*2* 
***3*** 
*****4***** 
***5*** 
*6*


 */

import java.util.Scanner;

public class q13_pattern3 {
    public static void main(String[] args) {
        int i = 0, j = 0;
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = sc.nextInt();
        sc.close();

        int mid = n/2;
        for(; i < n; i++){
            if(i < mid){
                for(j = 0; j < i*2-1; j++)
                    System.out.print("*");
                System.out.print(i + 1);
                for(j = 0; j < i*2-1; j++)
                    System.out.print("*");
                System.out.println("");
            }else{
                for(j = 0; j < n*2 -i*2 - 1; j++)
                    System.out.print("*");
                System.out.print(i + 1);
                for(j = 0; j < n*2 -i*2 - 1; j++)
                    System.out.print("*");
                System.out.println("");
            }
        }
        sc.close();
    }
}


