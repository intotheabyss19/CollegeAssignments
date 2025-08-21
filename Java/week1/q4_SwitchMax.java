import java.util.Scanner;

public class q4_SwitchMax {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter first number:");
        int a = sc.nextInt();
        System.out.println("Enter second number:");
        int b = sc.nextInt();
        Max m = new Max();
        m.findMax(a, b);
        sc.close();
    }
}

class Max {
    public void findMax(int a, int b) {
        int ch = (a > b) ? 1 : 2;
        switch (ch) {
            case 1:
                System.out.println(a + " is maximum");
                break;
            case 2:
                System.out.println(b + " is maximum");
                break;
        }
    }
}
