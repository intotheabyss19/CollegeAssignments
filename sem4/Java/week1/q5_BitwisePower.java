class q5_BitwisePower {
    Swapper swapper;
    public q5_BitwisePower() {
        swapper = new Swapper();
    }
    public static void main(String[] args) {
        q5_BitwisePower bit = new q5_BitwisePower();
        bit.swapper.swap();
    }
}

class Swapper {
    public void swap() {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        System.out.print("Enter the first number: ");
        int a = sc.nextInt();
        System.out.print("Enter the second number: ");
        int b = sc.nextInt();
        System.out.println("Before swap: a = " + a + ", b = " + b);
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
        System.out.println("After swap: a = " + a + ", b = " + b);
        sc.close();
    }
}