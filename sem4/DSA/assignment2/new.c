#include <stdio.h>
#include <stdlib.h>

#define MAXNAMESIZE 100
#define MAXCOACHES 5
#define SEATSPERCOACH 30
#define CONSTANT 100000
#define DATE "31-08-2024"
#define TRAIN "Brahmaputra Mail"
#define TRAINNO 15657

#define COLOR "\033[38;5;250m"
#define RESET "\033[0m"

typedef struct ticket {
    unsigned int pnr_number;
    char name[MAXNAMESIZE];
    unsigned short int age;
    unsigned short int coach;
    unsigned short int seatNum;
    unsigned short int bookingStatus;
    char SeniorCitizen;
} booking;

int BookTicket(booking chart[MAXCOACHES][SEATSPERCOACH]);
int CancelTicket(booking chart[MAXCOACHES][SEATSPERCOACH], int pnr);
int TicketPrinter(booking ticket);
int PrintChart(booking chart[MAXCOACHES][SEATSPERCOACH]);
void strGetter(char *str, int size);


int main()
{
    int ch, pnr;
    booking chart[MAXCOACHES][SEATSPERCOACH] = {0};  // Initialize chart with bookingStatus 0

    system("clear");
    printf("\n===============Welcome to Sikkim Railways===============\n");
    while(1)
    {
        printf("\nEnter '1' to Book a Ticket\
                \nEnter '2' to Cancel a Ticket\
                \nEnter '3' to Print a Ticket\
                \nEnter '4' to Print the chart\
                \nEnter '5' to Quit.\n\t==> ");
        scanf("%d", &ch);
        switch(ch)
        {
            case 1: 
                if(BookTicket(chart) == 0)
                    printf("\nTicket Booked Successfully\n");
                else
                    printf("\nERROR: Ticket Booking Unsuccessful\n");
                break;

            case 2: 
                printf("Enter a PNR Number: ");
                scanf("%d", &pnr);
                if(CancelTicket(chart, pnr) == 0)
                    printf("\nTicket Cancelled Successfully\n");
                else
                    printf("\nERROR: Ticket cancellation was unsuccessful\n");
                break;

            case 3:
                printf("Enter a PNR Number: ");
                scanf("%d", &pnr);
                int found = 0;
                for(int i = 0; i < MAXCOACHES; i++) {
                    for(int j = 0; j < SEATSPERCOACH; j++) {
                        if(chart[i][j].pnr_number == pnr) {
                            printf("Ticket for the PNR Number %d", pnr);
                            TicketPrinter(chart[i][j]);
                            found = 1;
                            break;
                        }
                    }
                    if(found) break;  // Stop searching once the ticket is found
                }
                if (!found)
                    printf("ERROR: Ticket Not Found\n");
                break;

            case 4:
                if(PrintChart(chart) == 0)
                    printf("\nChart Printed Successfully\n");
                else
                    printf("\nERROR: Printing Chart\n");
                break;

            case 5: 
                printf("\nProgram Exited.\n");
                return 0;

            default: 
                printf("Invalid Input\n");
        }
    }
    return 0;
}

int BookTicket(booking chart[MAXCOACHES][SEATSPERCOACH])
{
    int i, j, flag = 1;
    booking ticket_buffer;

    printf("Enter Name: ");
    strGetter(ticket_buffer.name, MAXNAMESIZE);
    printf("Enter Age: ");
    scanf("%d", &ticket_buffer.age);

    if(ticket_buffer.age >= 60) {
        ticket_buffer.SeniorCitizen = 'Y';
        // Prioritize lower berths for senior citizens (seat num divisible by 3)
        for(i = 0; i < MAXCOACHES && flag; i++) {
            for(j = 2; j < SEATSPERCOACH; j+=3) {
                if(chart[i][j].bookingStatus == 0) {
                    flag = 0;
                    break;
                }
            }
        }
    } else {
        ticket_buffer.SeniorCitizen = 'N';
    }

    // If no lower berth found or non-senior citizen, find any available seat
    if(flag) {
        for(i = 0; i < MAXCOACHES && flag; i++) {
            for(j = 0; j < SEATSPERCOACH; j++) {
                if(chart[i][j].bookingStatus == 0) {
                    flag = 0;
                    break;
                }
            }
        }
    }

    if(flag == 0) {
        ticket_buffer.coach = i + 1;
        ticket_buffer.seatNum = j + 1;
        ticket_buffer.bookingStatus = 1;
        ticket_buffer.pnr_number = CONSTANT + (i+1)*100 + (j+1);
    
        chart[i][j] = ticket_buffer;

        printf("\nHere's Your Ticket\n");
        TicketPrinter(chart[i][j]);
        return 0;
    } else {
        printf("Sorry, no seats available.\n");
        return 1;
    }
}

int CancelTicket(booking chart[MAXCOACHES][SEATSPERCOACH], int pnr)
{
    int i, j;
    for(i = 0; i < MAXCOACHES; i++) {
        for(j = 0; j < SEATSPERCOACH; j++) {
            if(chart[i][j].pnr_number == pnr) {
                chart[i][j].bookingStatus = 0;
                printf("Ticket cancelled for PNR %d.\n", pnr);
                return 0;
            }
        }
    }
    return 1;  // Ticket not found
}

int TicketPrinter(booking ticket)
{
    printf(COLOR"\n---Train Ticket for %s---\n", TRAIN);
    printf("x----------x-----------x------------x-----------------x\n");
    printf("|  PNR No: | Train No: |    Date:   | Senior Citizen: |\n");
    printf("|%8u  |%8d   | %10s |%9c        |\n", ticket.pnr_number, TRAINNO, DATE, ticket.SeniorCitizen);
    printf("x----------x-----------x------------x-----------------x\n");
    printf("| Name: %-29sAge: %-11d |\n", ticket.name, ticket.age);
    printf("| Coach No: %-25huSeat No: %-7hu |\n", ticket.coach, ticket.seatNum);
    printf("x----------x-----------x------------x-----------------x\n");
    printf("Wishing You a Happy Journey!\n"RESET);
    return 0;
}

int PrintChart(booking chart[MAXCOACHES][SEATSPERCOACH])
{
    int i, j;
    printf(COLOR"x------------x----------------------x-----x--------------x-------------x----------------x\n");
    printf("| PNR_Number |         Name         | Age | Coach Number | Seat Number | Senior Citizen |\n");
    printf("x------------x----------------------x-----x--------------x-------------x----------------x\n");
    for(i = 0; i < MAXCOACHES; i++) {
        for(j = 0; j < SEATSPERCOACH; j++) {
            if(chart[i][j].bookingStatus == 1) {
                printf("|%12u |%22s |%5hu |%14u |%13u |%16c |\n", chart[i][j].pnr_number, chart[i][j].name, chart[i][j].age, chart[i][j].coach, chart[i][j].seatNum, chart[i][j].SeniorCitizen);
            }
        }
    }
    printf("x------------x----------------------x-----x--------------x-------------x----------------x\n"RESET);
    return 0;
}

void strGetter(char *str, int size)
{
    getchar();  // Clear the newline character left in the buffer
    fgets(str, size - 2, stdin);
    int i = 0;
    while(str[i] != '\0' && str[i] != '\n')
        i++;
    str[i] = '\0';
}
