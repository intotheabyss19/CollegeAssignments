/*
The Uniting Multiple: In a land divided by numbers, 
two factions wish to unite under a single banner—the smallest multiple of both their chosen numbers. 
But unity doesn’t come easily; 
your JAVA program must calculate the lowest common multiple (LCM), 
even when the numbers seem irreconcilable. 
Will you find the number that brings harmony, 
or will the land remain divided?
*/

import java.util.Scanner;
class q11_LCM{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		System.out.print("Enter Number a: ");
		int a = sc.nextInt();
		System.out.print("Enter Number b: ");
		int b = sc.nextInt();
		
		System.out.println("The LCM of " + a + " and " + b + " is " + Utility.lcm(a,b));
	}
}

class Utility{
	static int lcm(int a, int b){
		for(int i = (a<b?a:b); i < a*b; i++)
			if(i % a== 0 && i % b == 0)
				return i;
		return 0;
	}
}