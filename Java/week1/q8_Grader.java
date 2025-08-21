import java.util.Scanner;

class Grade {
    private double percentage;
    private String grade;

    public Grade(double percentage) {
        this.percentage = percentage;
        this.grade = calculateGrade();
    }

    private String calculateGrade() {
        if (percentage >= 90) {
            return "A";
        } else if (percentage >= 80) {
            return "B";
        } else if (percentage >= 70) {
            return "C";
        } else if (percentage >= 60) {
            return "D";
        } else if (percentage >= 40) {
            return "E";
        } else {
            return "F";
        }
    }

    public String getGrade() {
        return grade;
    }
}

public class q8_Grader {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the percentage: ");
        double percentage = sc.nextDouble();
        Grade student1 = new Grade(percentage);
        System.out.println("Grade: " + student1.getGrade());
        sc.close();
    }
}