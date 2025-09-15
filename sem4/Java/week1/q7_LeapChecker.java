class q7_LeapChecker {
    public static void main(String[] args) {
        Year y = new Year();
        y.check();
    }
}

class Year {
    void check() {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        System.out.print("Enter year: ");
        int y = sc.nextInt();
        if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) {
            System.out.println(y + " is a leap year.");
        } else {
            System.out.println(y + " is not a leap year.");
        }
        sc.close();
    }
}