/* 6. Write a program to define a class Item containing code and price. Accept this data
for five objects using array of objects. Display code, price in tabular form and
also, display total price of all items.*/

import java.util.Scanner;

public class q6_PriceList {
	public static void main(String [] args) {
		System.out.println("Enter data for 5 items: ");
		Attribute[] L = new Attribute[5];
		Grid grid = new Grid();
		Input ip = new Input();
		for(int i = 0; i < 5; i++){
			System.out.print("Enter the item code: ");
			int code = ip.readInt();
			System.out.print("Enter the item price: ");
			int price = ip.readInt();
			L[i] = new Attribute(code, price);
		}

		grid.printHeader("Code", "Price");
		for(int i = 0; i < 5; i++) grid.printRow(L[i].code, L[i].price);
	}
}

class Grid {
    int maxHeaderLength = 0;
    public void printHeader(String... row) {
        // Finding out largest header
        for(String element : row) {
            System.out.print("+");
            for(int i = 0; i < element.length() + 2; i++) {
                System.out.print("-");
            }
        }
        System.out.println("+");
        for(String element : row) {
            System.out.printf("| %-"+element.length()+"s ", element);
            maxHeaderLength = maxHeaderLength > element.length() ? maxHeaderLength : element.length();
        }
        System.out.println("|");
        for(String element : row) {
            System.out.print("+");
            for(int i = 0; i < element.length() + 2; i++) {
                System.out.print("-");
            }
        }
        System.out.println("+");
    }

    public void printRow(int... values) {
        for(int value : values) {
            System.out.printf("| %-"+maxHeaderLength+"d ", value);
        }
        System.out.println(" |");
    }
}

class Attribute{
	int code = 0;
	int price = 0;
	public Attribute(int code,int price){
		this.code = code;
		this.price = price;
	}
}

class Input {
    private Scanner scanner;
	public Input() { scanner = new Scanner(System.in); }
	public int readInt() { return scanner.nextInt(); }
	public String readString() { return scanner.next(); }
}
