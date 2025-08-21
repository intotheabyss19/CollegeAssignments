/*
10. The Quest for the Greatest Divisor: 
Two rival tribes have set out on a quest to find their greatest common factor 
(GCF), a number that can unite them by dividing both without leaving a remainder. 
However, the journey is fraught with obstacles—sometimes the numbers are large, 
and other times, they’re too close to one another. 
Write a JAVA program that not only calculates the GCF but does so efficiently, 
even when the numbers challenge the very limits of your code.
*/

import java.util.Scanner;
class q10_GCF{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter Number a: ");
		int a = sc.nextInt();
		System.out.print("Enter Number b: ");
		int b = sc.nextInt();
		
		System.out.println("The GCF of " + a + " and " + b + " is " + Utility.gcf(a,b));
	}
}

class Utility{
	static int gcf(int a, int b){
		for(int i = (a<b?a:b); i > 0; i--)
			if(a % i == 0 && b % i == 0)
				return i;
		return 0;
	}
}

