import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a decimal number: ");
        double num = scanner.nextDouble();
        int reversed = reverseDecimal((int) num);
        System.out.println("Reversed number: " + reversed);
    }

    public static int reverseDecimal(int n) {
        int sign = n < 0 ? -1 : 1;
        n *= sign;
        int reversedN = 0;
        while (n > 0) {
            reversedN = reversedN * 10 + n % 10;
            n /= 10;
        }
        return sign * reversedN;
    }
}