public class q5_FactorialCalculator {
    public static void main(String[] args) {
        try {
            if (args.length == 0) {
                throw new ArrayIndexOutOfBoundsException("No input provided.");
            }

            int number = Integer.parseInt(args[0]);

            if (number == 0) {
                throw new IllegalArgumentException("Factorial for 0 is not allowed.");
            }

            long factorial = calculateFactorial(number);
            System.out.println("The factorial of " + number + " is: " + factorial);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println(e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: Please enter an integer value.");
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }

    private static long calculateFactorial(int number) {
        long result = 1;
        for (int i = 1; i <= number; i++) {
            result *= i;
        }
        return result;
    }
}
