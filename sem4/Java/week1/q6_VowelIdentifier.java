import java.util.Scanner;

public class q6_VowelIdentifier {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a letter: ");
        char c = sc.next().charAt(0);
        VowelChecker vc = new VowelChecker();
        vc.check(c);
        sc.close();
    }
}

class VowelChecker {
    public void check(char c) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            System.out.println(c + " is a vowel.");
        } else {
            System.out.println(c + " is a consonant.");
        }
    }
}