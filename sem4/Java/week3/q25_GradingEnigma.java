/*25. The Grading Enigma: Crafting the Perfect Evaluation System
In the innovative city of  Evalon, where every achievement and failure is meticulously 
recorded and analyzed, the Performance Council is tasked with ensuring that the evaluations 
of their workforce are fair, precise, and meaningful. As the city's top software architect, you 
have been summoned to design a critical component of their evaluation system: the Grader.
The Challenge:
The Performance Council needs a tool to translate raw performance scores into a clear and 
actionable letter grade. This will help them make informed decisions about employee 
promotions, raises, and training needs.
Your Mission:
1. Create the Grader Class:
oAttributes   and   Initialization:  Design  a  Grader  class  with  an  instance 
variable score that holds the performance score of an employee. Implement a 
constructor that ensures this score is properly initialized and falls within the 
acceptable range of 0 to 100. The constructor should handle edge cases and 
ensure no invalid scores are accepted.
oDetermine the Grade: Add a method called letterGrade() to the Grader 
class. This method will convert the numerical score into a letter grade based 
on Evalon’s grading criteria:
O for Outstanding (90-100)
E for Excellent (80-89)
A for Average (70-79)
B for Below Average (60-69)
C for Critically Low (50-59)
F for Failing (0-49)
2. Develop the Evaluation Scenario:
oImplement a GraderDemo class to put the Grader class to the test. This class 
should:
Prompt the user for a performance score.
Validate the input to ensure it’s not negative and does not exceed 100. 
If the input is invalid, inform the user with an appropriate message.
Create a Grader object with the valid score.
Invoke the letterGrade() method to determine the employee’s grade 
and display it in a user-friendly format.
The Outcome:
With your solution, the Performance Council of Evalon will have a reliable tool to convert 
numerical scores into clear, actionable grades, helping them maintain their high standards of 
evaluation and employee management. Your work will ensure that every employee’s 
performance is assessed fairly and transparently, driving the city towards excellence and 
innovation. Good luck, Architect of Code! The success of Evalon’s evaluation system rests in 
your hands. */

import java.util.InputMismatchException;
import java.util.Scanner;


public class q25_GradingEnigma {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int score;
        while (true) {
            try {
                System.out.print("Enter a performance score (0-100): ");
                score = scanner.nextInt();
                if (score < 0 || score > 100) {
                    System.out.println("Invalid score. Please enter a score between 0 and 100.");
                    continue;
                }
                break;
            } catch (InputMismatchException e) {
                System.out.println("Invalid input. Please enter a valid score.");
                scanner.next();
            }
        }

        Grader grader = new Grader(score);
        System.out.println("The letter grade is: " + grader.letterGrade());
        scanner.close();
    }
}
class Grader {
    private int score;

    public Grader(int score) {
        if (score < 0 || score > 100) {
            throw new IllegalArgumentException("Score must be between 0 and 100");
        }
        this.score = score;
    }

    public String letterGrade() {
        if (score >= 90) {
            return "O for Outstanding";
        } else if (score >= 80) {
            return "E for Excellent";
        } else if (score >= 70) {
            return "A for Average";
        } else if (score >= 60) {
            return "B for Below Average";
        } else if (score >= 50) {
            return "C for Critically Low";
        } else {
            return "F for Failing";
        }
    }
}