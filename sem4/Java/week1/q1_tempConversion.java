// Farenheit to celcius convertor

import java.util.Scanner;

class TempConvertor {
    public static double fToC(double fahrenheit) {
        return (fahrenheit - 32) * 5.0/9.0;
    }

    public static double cToF(double celsius) {
        return (celsius * 9.0/5.0) + 32;
    }
}

class q1_tempConversion {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter temperature value:");
        double temperature = scanner.nextDouble();
        System.out.println("Enter 'F' for Fahrenheit or 'C' for Celsius:");
        char unit = scanner.next().charAt(0);

        if (unit == 'F' || unit == 'f') {
            double celsius = TempConvertor.fToC(temperature);
            System.out.println(temperature + "°F is equal to " + celsius + "°C");
        } else if (unit == 'C' || unit == 'c') {
            double fahrenheit = TempConvertor.cToF(temperature);
            System.out.println(temperature + "°C is equal to " + fahrenheit + "°F");
        } else {
            System.out.println("Invalid unit");
        }
        scanner.close();
    }
}
