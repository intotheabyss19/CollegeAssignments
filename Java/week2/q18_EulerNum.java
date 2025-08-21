/*
18. The Infinite e: 
The mathematical monks of the Temple of Euler have discovered an infinite series 
that approximates the number "e", the base of natural logarithms. 
But the series never truly ends, and as you calculate more terms, 
the value of "e" becomes more precise. 
Write a JAVA program to compute "e" using the series expansion, 
but be prepared to decide when to stop. 
Will you find the true value of "e," or will you get lost in the infinite?
*/

class q18_EulerNum{
	public static void main(String args[]){
		java.util.Scanner sc = new java.util.Scanner(System.in);
		System.out.print("Enter the accuracy: ");
		int acc = sc.nextInt();

		System.out.println("The value of e is: " + (double) Utility.eulerNum(acc));
	}
}

class Utility{
	static double eulerNum(int acc){
		double e = 1;
		for ( int i = 1; i <= acc; i++ )
			e += (double)1 / factorial(i);
		return e;
	}

	static long factorial(int num){
		int fact = 1;
		for(; num > 0 ; num--)
			fact *= num;

		return fact;
	}
}

		