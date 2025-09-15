/*
1. The Buzz of the Century: You’re a detective tracking down a mysterious code known as a
Buzz number. A Buzz number has a peculiar trait: it's either divisible by 7 or contains the
digit 7 at the end. But there's a catch—sometimes, numbers play tricks, and
it’s up to you to write a JAVA program to determine if a given number is genuinely a Buzz
number. Beware, not all that ends in 7 is truly a Buzz!
*/

import java.util.Scanner;
class w2q1_Buzz{
	public static void main(String[] args){
		System.out.print("Enter an Integer: ");
		int n = Input.IntegerReader();
		System.out.print("The entered integer " + n);
		System.out.println(myUtils.isBuzz(n)?" is a Buzz number":" is not a Buzz Number");
	}
}

class Input{
	public static int IntegerReader(){
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		return n;
	}
}

class myUtils{
	public static boolean isBuzz(int n){
		return (n%7 == 0 || n%10 == 7);
	}
}