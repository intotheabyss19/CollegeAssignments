import java.util.Scanner;
public class q2_GeometryCalc {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Geometry Calculator");
        System.out.println("1. Rectangle");
        System.out.println("2. Circle");
        System.out.print("Choose an option: ");
        int option = scanner.nextInt();

        switch (option) {
            case 1:
                System.out.print("Enter length: ");
                double length = scanner.nextDouble();
                System.out.print("Enter width: ");
                double width = scanner.nextDouble();
                System.out.println("Area: " + getRectArea(length, width));
                System.out.println("Perimeter: " + getRectPerim(length, width));
                break;
            case 2:
                System.out.print("Enter radius: ");
                double radius = scanner.nextDouble();
                System.out.println("Area: " + getCircleArea(radius));
                System.out.println("Perimeter: " + getCirclePerim(radius));
                break;
            default:
            System.out.println("Invalid option");
        }
        scanner.close();
    }

    static double getRectArea(double length, double width) {
        return length * width;
    }

    static double getRectPerim(double length, double width) {
        return 2 * (length + width);
    }

    static double getCircleArea(double radius) {
        return Math.PI * Math.pow(radius, 2);
    }

    static double getCirclePerim(double radius) {
        return 2 * Math.PI * radius;
    }
}