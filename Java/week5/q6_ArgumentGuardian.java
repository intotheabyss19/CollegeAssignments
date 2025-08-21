class CheckArgumentException extends Exception {
    public CheckArgumentException(String message) {
        super(message);
    }
}

public class q6_ArgumentGuardian {
    public static void main(String[] args) {
        try {
            if (args.length < 5) {
                throw new CheckArgumentException("Exactly five numbers are required.");
            }

            int sum = 0;
            for (String arg : args) {
                sum += Integer.parseInt(arg);
            }

            System.out.println("The sum of the five numbers is: " + sum);
        } catch (CheckArgumentException e) {
            System.out.println(e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: Please ensure all arguments are integers.");
        }
    }
}
