/*4. Image Processing with Matrices
You're working on a simple image processing task where two images are represented as 2D 
arrays of pixel values. To apply certain filters, you need to calculate the sum of these two 
matrices, representing the pixel-wise addition of two images. Your task is to write a Java 
program that accurately computes the resulting image after summing these two 2D arrays. 
Can you ensure that your solution handles different image sizes correctly?
*/
import java.util.Scanner;

public class q4_ImageProcessingWithMatrices {
    public static void main(String[] args) {
        MxOperations mxOperations = new MxOperations();

        System.out.println("Enter number of rows for matrix 1: ");
        int row1 = mxOperations.input.readNum();
        System.out.println("Enter number of columns for matrix 1: ");
        int col1 = mxOperations.input.readNum();

        System.out.println("Enter elements of matrix 1: ");
        int[][] matrix1 = mxOperations.getMatrix(row1, col1);

        System.out.println("Enter number of rows for matrix 2: ");
        int row2 = mxOperations.input.readNum();
        System.out.println("Enter number of columns for matrix 2: ");
        int col2 = mxOperations.input.readNum();

        System.out.println("Enter elements of matrix 2: ");
        int[][] matrix2 = mxOperations.getMatrix(row2, col2);

        int[][] result = mxOperations.addMatrices(matrix1, matrix2);

        if (result != null) {
            System.out.println("Matrix 1: ");
            mxOperations.printMatrix(matrix1);
            System.out.println("Matrix 2: ");
            mxOperations.printMatrix(matrix2);
            System.out.println("Result: ");
            mxOperations.printMatrix(result);
        }
    }
}

class MxOperations {
    Input input = new Input(new Scanner(System.in));
    public int[][] getMatrix(int m, int n) {
        int[][] matrix = new int[m][n];
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                matrix[i][j] = input.readNum();
            }
        }
        return matrix;
    }

    public void printMatrix(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public int[][] addMatrices(int[][] matrix1, int[][] matrix2) {
        int[][] result = new int[matrix1.length][matrix1[0].length];
        for (int i = 0; i < matrix1.length; i++) {
            for (int j = 0; j < matrix1[0].length; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        return result;
        }
    }
}

class Input {
    private Scanner sc = new Scanner(System.in);
    public Input(Scanner sc) {
        this.sc = sc;
    }
    public int readNum() {
        return sc.nextInt();
    }
}