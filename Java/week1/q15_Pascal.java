import java.util.Scanner;

class PascalTriangle {
    private int n;

    public PascalTriangle(int n) {
        this.n = n;
    }

    public void printPascal() {
        int[][] pascal = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    pascal[i][j] = 1;
                } else {
                    pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int k = 0; k <= n - i; k++){
                System.out.print(" ");
            }
            for (int j = 0; j <= i; j++) {
                System.out.print(pascal[i][j] + " ");
            }
            System.out.println();
        }
    }
}

public class q15_Pascal {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = sc.nextInt();
        PascalTriangle pascalTriangle = new PascalTriangle(n);
        System.out.println("Pascal triangle for input " + n + ": ");
        pascalTriangle.printPascal();
        sc.close();
    }
}
