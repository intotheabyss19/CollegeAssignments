/*
The Counting Sorcerer: 
A powerful sorcerer has summoned you to count the digits of a number, 
but there’s a trick—some numbers appear simple on the surface 
but hide their true length behind leading zeros. 
Write a JAVA program that accurately counts the digits, 
no matter what form the number takes, 
and remember—the sorcerer’s test is not as easy as it seems.
*/

import java.util.Scanner;

class q12_TrueLengthCounter{
	public static void main(String args[]){
		Scanner sc = new Scanner(System.in);
		String Num = new String();
		System.out.print("Enter a Number: ");
		Num = sc.nextLine();
		
		System.out.println("The true length of the given number is: " + Utility.trueLengthCounter(Num));
	}
}

class Utility{
	static int trueLengthCounter(String S){
		return S.length();
	}
}