class RangeException extends Exception {
    public RangeException(String message) {
        super(message);
    }
}

public class q7_StudentExaminationDatabase {
    public static void main(String[] args) {
        try {
            if (args.length < 7) {
                System.out.println("Please provide the student's name followed by six marks.");
                return;
            }

            String studentName = args[0];
            int totalMarks = 0;

            for (int i = 1; i <= 6; i++) {
                int mark = Integer.parseInt(args[i]);
                if (mark < 0 || mark > 50) {
                    throw new RangeException("Mark for subject " + i + " is out of range: " + mark);
                }
                totalMarks += mark;
            }

            double percentage = (totalMarks / 300.0) * 100;
            System.out.println("Student Name: " + studentName);
            System.out.println("Total Marks: " + totalMarks);
            System.out.println("Percentage: " + percentage + "%");

        } catch (RangeException e) {
            System.out.println(e.getMessage());
        } catch (NumberFormatException e) {
            System.out.println("Invalid input: Please ensure all marks are integers.");
        }
    }
}
