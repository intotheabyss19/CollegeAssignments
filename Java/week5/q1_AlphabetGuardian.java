/*
1. In the mystical land of Stringia, you have been chosen as the Alphabet Guardian. 
* Your task is to maintain a running total of all alphabetic characters passed to you, 
* ensuring that only valid alphabetic characters enter the sacred vault. 
* If a non-alphabetic character attempts to breach the vault, you must raise an alarm by throwing an exception called 
* NonAlphabeticCharacterException.

Your mission:
* Write a class AlphabetGuardian that keeps a running total of all alphabetic characters passed to it.
* If a non-alphabetic character is passed, throw a custom exception
* NonAlphabeticCharacterException.

* Provide a method addCharacter(char c) that adds a valid character to the total or throws the exception if it's invalid.

Instructions:
• Define the custom exception NonAlphabeticCharacterException.
• Implement the AlphabetGuardian class with a method addCharacter(char c) that checks if the character is alphabetic.
• In case of a non-alphabetic character, throw the custom exception.
• Provide a method to retrieve the total number of valid characters stored so far.

Output Format:
• If all characters are valid, print the running total.
• If an invalid character is passed, print a custom error message.
*/

import java.util.Scanner;

class NonAlphabeticCharacterException extends Exception {
    public NonAlphabeticCharacterException(String message) {
        super(message);
    }
}

class AlphabetGuardian {
    private String PureAlpha = "";

    void addCharacter(char c) throws NonAlphabeticCharacterException {
        if (!Character.isAlphabetic(c)) {
            throw new NonAlphabeticCharacterException("Error... Non-alphabetic character encountered: " + c);
        }
        PureAlpha += c;
    }

    void print() {
        System.out.println("The Pure String is: " + PureAlpha);
    }
}

public class q1_AlphabetGuardian {
    public static void main (String[] args) {
        System.out.print("Enter an Alphabetic String: ");

        Input ip = new Input();
        String S = ip.readString();
        int flag = 0;

        System.out.println("The entered string is: " + S);
        AlphabetGuardian AG = new AlphabetGuardian();
        char chars[] = S.toCharArray();
        for (int i = 0; i < S.length(); i++) {
            try {
                AG.addCharacter(chars[i]);
            } catch (NonAlphabeticCharacterException nace) {
                System.out.println(nace.getMessage());
                flag = 1;
            }
        }
        AG.print();

        if(flag == 1)
            System.out.println("Please don't enter non-alphabetic characters in the holy land of alphabets...");
        System.out.println("\nExiting the program...");
    }
}


class Input {
    private Scanner scanner;

    public Input() {
        scanner = new Scanner(System.in);
    }
    public String readString() {
        return scanner.nextLine();
    }
}
