class ArithmeticOperationException extends Exception {
    public ArithmeticOperationException(String message) {
        super(message);
    }
}

public class q8_ComplexEquationCalculator {
    public static void main(String[] args) {
        try {
            String equation = "10 + 20 * (30 / 5) ^ 2 - 5"; // Example equation
            double result = evaluateEquation(equation);
            System.out.println("The result of the equation is: " + result);
        } catch (ArithmeticOperationException e) {
            System.out.println(e.getMessage());
        }
    }

    private static double evaluateEquation(String equation) throws ArithmeticOperationException {
        String[] tokens = equation.split(" ");
        double result = 0;

        for (int i = 0; i < tokens.length; i++) {
            if (tokens[i].equals("+")) {
                i++;
                result += parseNumber(tokens[i]);
            } else if (tokens[i].equals("-")) {
                i++;
                result -= parseNumber(tokens[i]);
            } else if (tokens[i].equals("*")) {
                i++;
                result *= parseNumber(tokens[i]);
            } else if (tokens[i].equals("/")) {
                i++;
                double divisor = parseNumber(tokens[i]);
                if (divisor == 0) {
                    throw new ArithmeticOperationException("Division by zero error: Cannot divide by zero.");
                }
                result /= divisor;
            } else if (tokens[i].equals("^")) {
                i++;
                result = Math.pow(result, parseNumber(tokens[i]));
            } else {
                result = parseNumber(tokens[i]);
            }
        }

        if (result == Double.POSITIVE_INFINITY || result == Double.NEGATIVE_INFINITY) {
            throw new ArithmeticOperationException("Overflow error: The result exceeds the maximum limit.");
        }

        return result;
    }

    private static double parseNumber(String token) throws ArithmeticOperationException {
        try {
            return Double.parseDouble(token);
        } catch (NumberFormatException e) {
            throw new ArithmeticOperationException("Invalid number format: " + token);
        }
    }
}
