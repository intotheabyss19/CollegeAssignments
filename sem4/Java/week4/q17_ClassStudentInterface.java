import java.util.Scanner;

class Input {
    Scanner sc = new Scanner(System.in);
    String ipStr = "";
    void Input(String ipStr) {
        ipStr = sc.nextLine();
    }

    int ipInt() {
        return Integer.parseInt(ipStr);
    }

    int ipfloat() {
        return Float.parseFloat(ipStr);
    }

    String ipString() {
        return ipStr;
    }
}

interface Exam {
    double Percent_cal();
}

class Student {
    String name = "";
    int roll_no;
    float marks1, marks2;

    void show() {
        System.out.print("Name: " + name);
        System.out.print("Roll No: " + roll_no);
        System.out.print("Marks1: " + marks1);
        System.out.print("Marks2: " + marks2);
    }
}

class Result extends Student implements Exam {

    float percentage;
    float Percent_cal(float percentage) {
        percentage = (marks1 + marks2) / 200;
    }

    void perdisplay() {
        Percent_cal(percentage);
        System.out.println("Percentage: " + percentage);
    }
}

public class q17_ClassStudentInterface {
    public static void main(String [] args) {
        Result s = new Result();
        Input ip = new Input();
        s.name = ip.ipString();
        s.roll_no = ip.ipInt();
        s.marks1 = ip.ipfloat();
        s.marks2 = ip.ipfloat();

        s.show();

        s.perdisplay();

    }
}

