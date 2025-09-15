/*10. Create an interface Department containing  attributes deptName and deptHead. It 
also has abstract methods for printing the attributes. Create a class hostel containing 
hostelName,  hostelLocation  and  numberofRooms.  The  class  contains  methods  for 
getting and printing the attributes. Then write Student class extending the Hostel class 
and  implementing  the  Department  interface.  This  class  contains  attributes 
studentName, regdNo,  electiveSubject and avgMarks. Write suitable getData and 
printData methods  for  this  class.  Also  implement  the  abstract  methods  of  the 
Department interface. Write a  driver class to test the Student class. The program 
should be menu driven containing the options: 
a. Admit new student 
b. Migrate a student 
c. Display details of a student 
For the third option a search is to be made on the basis of the entered 
registration number.  */


// Interface Department
interface Department {
    String deptName = "";
    String deptHead = "";

    void printDepartmentDetails() {
        System.out.println("Inside interface");
    }
}

// Class Hostel
class Hostel {
    String hostelName;
    String hostelLocation;
    int numberOfRooms;

    public Hostel(String hostelName, String hostelLocation, int numberOfRooms) {
        this.hostelName = hostelName;
        this.hostelLocation = hostelLocation;
        this.numberOfRooms = numberOfRooms;
    }

    public void printHostelDetails() {
        System.out.println("Hostel Name: " + hostelName);
        System.out.println("Hostel Location: " + hostelLocation);
        System.out.println("Number of Rooms: " + numberOfRooms);
    }
}

// Class Student
class Student extends Hostel implements Department {
    String studentName;
    int regdNo;
    String electiveSubject;
    double avgMarks;

    public Student(String hostelName, String hostelLocation, int numberOfRooms, String studentName, int regdNo, String electiveSubject, double avgMarks) {
        super(hostelName, hostelLocation, numberOfRooms);
        this.studentName = studentName;
        this.regdNo = regdNo;
        this.electiveSubject = electiveSubject;
        this.avgMarks = avgMarks;
        //Department.deptName = "Computer Science";
        //Department.deptHead = "Dr. Smith";
    }

    public void getData() {
        System.out.println("Enter student details:");
        Input input = new Input();
        studentName = input.getString("Enter student name: ");
        regdNo = input.getInteger("Enter registration number: ");
        electiveSubject = input.getString("Enter elective subject: ");
        avgMarks = input.getDouble("Enter average marks: ");
    }

    public void printData() {
        System.out.println("Student Details:");
        System.out.println("Student Name: " + studentName);
        System.out.println("Registration Number: " + regdNo);
        System.out.println("Elective Subject: " + electiveSubject);
        System.out.println("Average Marks: " + avgMarks);
        printHostelDetails();
        printDepartmentDetails();
    }

    @Override
    public void printDepartmentDetails() {
        System.out.println("Department Name: " + Department.deptName);
        System.out.println("Department Head: " + Department.deptHead);
    }
}

// Input class
class Input {
    java.util.Scanner scanner = new java.util.Scanner(System.in);

    public String getString(String prompt) {
        System.out.print(prompt);
        return scanner.nextLine();
    }

    public int getInteger(String prompt) {
        System.out.print(prompt);
        return scanner.nextInt();
    }

    public double getDouble(String prompt) {
        System.out.print(prompt);
        return scanner.nextDouble();
    }
}

// Driver class
public class q7_HostelManagement {
    public static void main(String[] args) {
        Student[] students = new Student[10];
        int studentCount = 0;

        while (true) {
            System.out.println("1. Admit new student");
            System.out.println("2. Migrate a student");
            System.out.println("3. Display details of a student");
            System.out.println("4. Exit");
            Input input = new Input();
            int choice = input.getInteger("Enter your choice: ");

            switch (choice) {
                case 1:
                    if (studentCount < 10) {
                        Student student = new Student("Hostel A", "Delhi", 100, "", 0, "", 0.0);
                        student.getData();
                        students[studentCount] = student;
                        studentCount++;
                    } else {
                        System.out.println("Hostel is full.");
                    }
                    break;
                case 2:
                    break;
                case 3:
                    int regdNo = input.getInteger("Enter registration number: ");
                    boolean found = false;
                    for (Student student : students) {
                        if (student != null && student.regdNo == regdNo) {
                            student.printData();
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        System.out.println("Student not found.");
                    }
                    break;
                case 4:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }
}
