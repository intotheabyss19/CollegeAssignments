import java.util.Scanner;

public class q10_Binary {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a number:");
        int num = sc.nextInt();
        System.out.println("Enter the index of the bit to check (0-indexed):");
        int n = sc.nextInt();
        BitChecker bc = new BitChecker();
        boolean bitValue = bc.checkBit(num, n);
        System.out.println("The value of the " + n + "th bit is: " + bitValue);
        sc.close();
    }
}

class BitChecker {
    public boolean checkBit(int num, int n) {
        return ((num >> n) & 1) == 1;
    }
}