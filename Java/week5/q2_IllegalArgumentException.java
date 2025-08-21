public class q2_IllegalArgumentException {

    private static final long[] factorials = new long[21];

    static {
        factorials[0] = 1; 
        for (int i = 1; i <= 20; i++) {
            factorials[i] = factorials[i - 1] * i;
        }
    }

    public static long getFactorial(int x) {
        if (x < 0) {
            throw new IllegalArgumentException("Value of x must be positive");
        }
        if (x > 20) {
            throw new IllegalArgumentException("Result will overflow");
        }
        return factorials[x];
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Factorial <number>");
            return;
        }

        try {
            int x = Integer.parseInt(args[0]);
            long result = getFactorial(x);
            System.out.println("Factorial of " + x + " is: " + result);
        } catch (IllegalArgumentException i) {
            System.out.println(i.getMessage());
        }
    }
}
