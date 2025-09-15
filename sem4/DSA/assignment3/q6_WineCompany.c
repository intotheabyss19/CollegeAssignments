/*6.Sikkim Wine Company has a policy of selling the newest wine bottles first and the oldest wine bottles last,
since old wine bottles are considered more flavourful and can be sold at a higher price. So, the company
maintains a stack to store the information of the wine bottles, where the newest bottle to be pushed to the
stack is the first one to be removed from the stack and sold. The oldest bottle in the stack is the last one to
be removed from the stack and sold.
Write a program to create a stack, using an array of structures, to store the information of wine bottles so
that each element of the stack is a structure object containing the following details of one wine bottle:
i)Serial number of the bottle, srl
ii)Date of manufacture of the bottle, date
iii)Name of the vineyard for the bottle, vinyrd
iv)Price of the bottle, price
The price of each wine bottle is initially set and then later updated according to the following scheme:
when a bottle is pushed to the stack, its initial price is 500 rupees, and then every time a new bottle is
pushed to the stack, the price of all the previously existing bottles of the stack (i.e. all bottles except the
new bottle which is being pushed to the stack) is increased by 50 rupees.
Your program will initially set the stack to be empty, after taking the maximum size of the stack max as
input from the user, and provide a menu-based interface containing the following options:
i)“Add New Bottle”, which pushes a new bottle into the stack after taking its srl, date, vinyrd, and
initial price as input from the user,
ii)“Sell Bottle”, which removes one bottle from the stack and shows the final selling price of the
bottle, along with its srl, date, and vinyrd, in a reader-friendly format resembling a bill,
iii)“Display Stock”, which shows the srl, date, vinyrd, and current price of all bottles in the stack in a
reader-friendly tabular format, and
iv)“Quit”, which lets the user quit the menu which otherwise is repeatedly displayed in a loop.
After the user quits the menu, display as the final output of your program the total profit of the company if
the manufacturing cost of every bottle in the stack is 450 rupees. Note that the “Add New Bottle” option
and the “Sell Bottle” option should handle the overflow condition and the underflow condition
respectively, and display appropriate messages.*/

#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int srl;
    char date[20];
    char vinyrd[50];
    int price;
} Wine;

void displayMenu() {
    printf("\n\tMenu:\n");
    printf("\t1. Add New Bottle\n");
    printf("\t2. Sell Bottle\n");
    printf("\t3. Display Stock\n");
    printf("\t4. Quit\n");
}

void addNewBottle(Wine stack[], int *top, int max) {
    if (*top == max - 1) {
        printf("\nStack is full. Cannot add new bottle.\n");
        return;
    }

    printf("Enter serial number: ");
    scanf("%d", &stack[*top + 1].srl);
    printf("Enter date of manufacture: ");
    scanf("%s", stack[*top + 1].date);
    printf("Enter name of vineyard: ");
    scanf("%s", stack[*top + 1].vinyrd);
    stack[*top + 1].price = 500;

    for (int i = 0; i <= *top; i++) {
        stack[i].price += 50;
    }

    (*top)++;
    printf("\nBottle Added Successfully.\n");
}

int sellBottle(Wine stack[], int *top, int *totalProfit) {
    if (*top == -1) {
        printf("\nStack is empty. No bottles to sell.\n");
        return 0;
    }
    (*totalProfit) += stack[*top].price - 450;
    printf("Selling bottle with serial number: %d\n", stack[*top].srl);
    printf("Date of manufacture: %s\n", stack[*top].date);
    printf("Name of vineyard: %s\n", stack[*top].vinyrd);
    printf("Selling price: %d\n", stack[*top].price);

    (*top)--;
    return 1;
}

void displayStock(Wine stack[], int top) {
    if (top == -1) {
        printf("Stack is empty. No bottles to display.\n");
        return;
    }

    printf("Serial Number\tDate of Manufacture\tName of Vineyard\tCurrent Price\n");
    for (int i = 0; i <= top; i++) {
        printf("%8d\t\t%6s\t\t%s\t\t%d\n", stack[i].srl, stack[i].date, stack[i].vinyrd, stack[i].price);
    }
}

int main() {
    int max;
    int totalProfit = 0;
    printf("Enter maximum size of stack: ");
    scanf("%d", &max);

    Wine stack[MAX_SIZE];
    int top = -1;

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewBottle(stack, &top, max);
                break;
            case 2:
                sellBottle(stack, &top, &totalProfit);
                break;
            case 3:
                displayStock(stack, top);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    printf("Total profit: %d\n", totalProfit);
    return 0;
}
