/*
10. Finding the Smallest Value in a Sensor Array
In a network of IoT devices, you receive an array of readings from different sensors. 
To identify potential issues, you need to find the smallest reading in this array. 
Write a Java program that takes n elements from the user and determines the smallest value. 
How will you ensure your solution is robust enough to handle noisy or inconsistent data from the sensors?
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class q10_SmallestNo {
    public static void main(String[] args) throws IOException {
        Input in = new Input();
        int n = in.getNum();
        int[] readings = in.getReadings(n);

        Sa sa = new Sa(readings);
        int smallest = sa.findSmallest();

        System.out.println("The smallest value is: " + smallest);
    }
}
class Input{
    BufferedReader r = new BufferedReader(new InputStreamReader(System.in));

    int getNum() throws IOException {
        System.out.print("Enter the number of elements: ");
        return Integer.parseInt(r.readLine());
    }

    int[] getReadings(int n) throws IOException {
        int[] readings = new int[n];
        for (int i = 0; i < n; i++) {
            System.out.print("Enter sensor reading " + (i + 1) + ": ");
            readings[i] = Integer.parseInt(r.readLine());
        }
        return readings;
    }
}

class Sa {
    int[] readings;

    Sa(int[] readings) {
        this.readings = readings;
    }

    int findSmallest() {
        int smallest = readings[0];
        for (int i = 1; i < readings.length; i++) {
            if (readings[i] < smallest) {
                smallest = readings[i];
            }
        }
        return smallest;
    }
}
