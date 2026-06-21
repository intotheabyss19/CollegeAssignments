/*3. Customer Service Queue Management
Imagine you're developing a customer service application for a large retail store. The system 
needs to manage customers waiting in line using a queue implemented with an array. As 
customers arrive, they are added to the end of the queue, and the service desk attends to them 
in a first-come, first-served manner. Can you write a Java program to simulate this queue 
management system and ensure that it can handle both busy and quiet periods effectively?*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class q3_CustomerServiceQueue {
    public static void main(String[] args) {
        CustomerServiceQueueSystem queueSystem = new CustomerServiceQueueSystem();
        Input input = new Input();

        while (true) {
            try {
                System.out.print("Enter a command\n'1' Add customer to queue:\n'2' Serve next customer:\n'3' Print queue status:\n'4' Quit:\n\t==>");
                String cmd = input.readInput();

                switch (cmd) {
                    case "1":
                        System.out.println("Enter customer name: ");
                        String customerName = input.readInput();
                        queueSystem.addCustomerToQueue(customerName);
                        break;
                    case "2":
                        queueSystem.serveNextCustomer();
                        break;
                    case "3":
                        queueSystem.printQueueStatus();
                        break;
                    case "4":
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid command. Please try again.");
                }
            } catch (IOException e) {
                System.out.println("Invalid cmd. Please try again.");
                System.err.println("Error: " + e.getMessage());
            }
        }
    }
}

class CustomerServiceQueueSystem {
    private Customer[] queue;
    private int front;
    private int rear;
    private int size;

    public CustomerServiceQueueSystem() {
        queue = new Customer[10];
        front = 0;
        rear = 0;
        size = 0;
    }

    public void addCustomerToQueue(String customerName) {
        if (size == queue.length) {
            System.out.println("Queue is full. Cannot add more customers.");
            return;
        }
        Customer customer = new Customer(customerName);
        queue[rear] = customer;
        rear = (rear + 1) % queue.length;
        size++;
    }

    public void serveNextCustomer() {
        if (size == 0) {
            System.out.println("Queue is empty. No customers to serve.");
            return;
        }
        Customer customer = queue[front];
        System.out.println("Serving customer: " + customer.getName());
        front = (front + 1) % queue.length;
        size--;
    }

    public void printQueueStatus() {
        System.out.println("Queue status:");
        for (int i = 0; i < size; i++) {
            int index = (front + i) % queue.length;
            System.out.println((i + 1) + ". " + queue[index].getName());
        }
    }
}

class Customer {
    private String name;

    public Customer(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}

class Input {
    private BufferedReader bufferedReader;

    public Input() {
        bufferedReader = new BufferedReader(new InputStreamReader(System.in));
    }

    public String readInput() throws IOException {
        return bufferedReader.readLine();
    }
}
