/*2. Web Browser Navigation Simulation
Your program should be able to push new URLs onto the stack as users navigate, pop URLs 
when users hit the "back" button, and handle edge cases like an empty stack when there are 
no more pages to go back to. You're tasked with simulating the "back" and "forward" 
navigation functionality of a web browser. To do this, you need to implement a stack using an 
array in Java. How will you ensure that your stack-based navigation is efficient and error-
free?*/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Stack;

public class q2_NavigationSimulation {
    public static void main(String[] args) {
        WebBrowser browser = new WebBrowser();
        Input input = new Input();

        while (true) {
            try {
                System.out.print("Enter a command\n'1' Navigate forward:\n'2' Navigate back:\n'3' Add a new URL:\n'4' Delete an existing URL:\n'5' Quit:\n\t==>");
                String cmd = input.readInput();

                switch (cmd) {
                    case "1":
                        browser.goForward();
                        browser.printCurrentPage();
                        break;
                    case "2":
                        browser.goBack();
                        browser.printCurrentPage();
                        break;
                    case "3":
                        System.out.println("Enter a URL: ");
                        String url = input.readInput();
                        browser.navigateTo(url);
                        browser.printCurrentPage();
                        break;
                    case "4":
                        System.out.println("Delete URL functionality not implemented yet.");
                        break;
                    case "5":
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

class WebBrowser {
    private Stack<String> backwardStack;
    private Stack<String> forwardStack;
    private String currentPage;

    public WebBrowser() {
        backwardStack = new Stack<>();
        forwardStack = new Stack<>();
        currentPage = "";
    }

    public void navigateTo(String url) {
        if (!currentPage.isEmpty()) {
            backwardStack.push(currentPage);
        }
        currentPage = url;
        forwardStack.clear();
    }

    public void goBack() {
        if (!backwardStack.isEmpty()) {
            forwardStack.push(currentPage);
            currentPage = backwardStack.pop();
        } else {
            System.out.println("You are at the beginning of your navigation history.\n");
        }
    }

    public void goForward() {
        if (!forwardStack.isEmpty()) {
            backwardStack.push(currentPage);
            currentPage = forwardStack.pop();
        } else {
            System.out.println("You are at the end of your navigation history.\n");
        }
    }

    public void printCurrentPage() {
        System.out.println("Current page: " + currentPage);
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