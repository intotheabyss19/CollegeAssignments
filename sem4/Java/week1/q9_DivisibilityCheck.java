public class q9_DivisibilityCheck {
    public static void main(String[] args) {
        NumAnalyze na = new NumAnalyze();
        na.checkDivisibility();
    }
}

class NumAnalyze {
    void checkDivisibility() {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        System.out.println("Enter a number:");
        int num = sc.nextInt();
        String result = (num % 7 == 0 && num % 11 == 0) ? "Divisible by both 7 and 11" : "Not divisible by both 7 and 11";
        System.out.println(result);
        sc.close();
    }
}