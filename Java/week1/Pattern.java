/*
XI. Problem: You are working on a graphical interface for a star pattern generator in a
children's learning application. This feature needs to display various star patterns to
engage young users. Write a Java program that outputs the following star pattern:
    *
   ***
  *****
 *******
*********
*/

import java.io.*;

class P{
	public static void patternPrinter(){
		int i, j, k;
		for(i = 0; i < 5; i++){
			System.out.print("*");
		}
	}
}

class Pattern{
	public static void main(String[] args){
		P.patternPrinter();
	}

}