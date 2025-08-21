/*24. The Constructor Chronicles: Building the Foundation of a Java Empire
In the bustling world of Java development, constructors are the architects who lay the 
foundation for every class object. You’ve been hired by a top-tier software company, 
Constructor Dynamics, renowned for its mastery over object creation. Your challenge is to 
design a robust Java class called Building, which will serve as the blueprint for all future 
infrastructure in the company's high-tech city project, JavaMetropolis.
Your mission has three critical phases:
1. Phase 1 - The Default Blueprint: Create a Building class with a 0-arguments 
constructor, representing the basic blueprint that initiates all essential structural 
parameters to their default states. This constructor should print a message confirming 
that a standard building has been initialized.
2. Phase   2   -   Custom   Designs:   Enhance   the   Building   class   by   introducing   a 
parameterized constructor that allows architects to specify the building’s height, 
width, and depth. This constructor will enable the creation of custom-designed 
buildings in JavaMetropolis, reflecting the diverse needs of the city’s futuristic 
skyline.
3. Phase 3 - The Copying Architect: Implement a copy constructor that can duplicate 
an existing Building object. This constructor is crucial for replicating successful 
designs in other areas of the city without altering the original structure.
4. Bonus Phase - Overloaded Creations: Demonstrate constructor overloading by 
adding multiple constructors to the Building class, allowing for various combinations 
of parameters (e.g., height and width only, height and depth only, etc.). Each 
overloaded constructor should initialize the building with the provided parameters 
while setting the rest to default values.
Your task is to merge these phases into a single, cohesive Java program that showcases the 
power and flexibility of constructors in building the future of JavaMetropolis. Good luck, 
Architect of Code! The future of JavaMetropolis rests in your hands */

import java.util.Scanner;

public class q24_ConstructorChronicles {
    public static void main(String[] args) {
        Input input = new Input();

        System.out.println("Enter building details:");
        System.out.print("Height: ");
        int height = input.readInt();
        System.out.print("Width: ");
        int width = input.readInt();
        System.out.print("Depth: ");
        int depth = input.readInt();

        Building building1 = new Building(height, width, depth);
        building1.printBuildingDetails();

        Building building2 = new Building(building1);
        building2.printBuildingDetails();

        Building building3 = new Building(height, width);
        building3.printBuildingDetails();

        Building building4 = new Building(height, depth);
        building4.printBuildingDetails();

        Building building5 = new Building(width, depth);
        building5.printBuildingDetails();
    }
}


class Input {
    private Scanner scanner;

    public Input() {
        scanner = new Scanner(System.in);
    }

    public int readInt() {
        return scanner.nextInt();
    }

    public double readDouble() {
        return scanner.nextDouble();
    }

    public String readString() {
        return scanner.next();
    }
}

class Building {
    private int height;
    private int width;
    private int depth;

    // Phase 1 - The Default Blueprint
    public Building() {
        this.height = 10;
        this.width = 10;
        this.depth = 10;
        System.out.println("A standard building has been initialized.");
    }

    // Phase 2 - Custom Designs
    public Building(int height, int width, int depth) {
        this.height = height;
        this.width = width;
        this.depth = depth;
        System.out.println("A custom building has been initialized.");
    }

    // Phase 3 - The Copying Architect
    public Building(Building building) {
        this.height = building.height;
        this.width = building.width;
        this.depth = building.depth;
        System.out.println("A building has been duplicated.");
    }

    // Bonus Phase - Overloaded Creations
    public Building(int height, int width) {
        this.height = height;
        this.width = width;
        this.depth = 10;
        System.out.println("A building with height and width has been initialized.");
    }

    public Building(int height, int depth) {
        this.height = height;
        this.width = 10;
        this.depth = depth;
        System.out.println("A building with height and depth has been initialized.");
    }

    public Building(int width, int depth) {
        this.height = 10;
        this.width = width;
        this.depth = depth;
        System.out.println("A building with width and depth has been initialized.");
    }

    public void printBuildingDetails() {
        System.out.println("Building Details:");
        System.out.println("Height: " + height);
        System.out.println("Width: " + width);
        System.out.println("Depth: " + depth);
    }
}

