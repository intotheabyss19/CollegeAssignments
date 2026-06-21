public class q3_NumCategorizer {
    public static void main(String[] args) {
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        System.out.print("Enter a number: ");
        int num = scanner.nextInt();
        scanner.close();

        if (num > 0) {
            System.out.println(num + " is a positive number.");
        } else if (num < 0) {
            System.out.println(num + " is a negative number.");
        } else {
            System.out.println("You've entered zero.");
        }

        if (num % 2 == 0) {
            System.out.println(num + " is an even number.");
        } else {
            System.out.println(num + " is an odd number.");
        }
    }
}