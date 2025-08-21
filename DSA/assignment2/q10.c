#include <stdio.h>
#include <stdlib.h>

// Define structure for storing player data
struct Player {
    char name[50];
    int runs1;
    int runs2;
};

// Function to input player data
void inputPlayerData(struct Player team[], int teamSize, char *teamName) {
    printf("Enter details for team %s:\n", teamName);
    for (int i = 0; i < teamSize; i++) {
        printf("Player %d name: ", i + 1);
        scanf("%s", team[i].name);
        printf("Runs scored by %s in 1st innings: ", team[i].name);
        scanf("%d", &team[i].runs1);
        printf("Runs scored by %s in 2nd innings: ", team[i].name);
        scanf("%d", &team[i].runs2);
    }
}

// Function to calculate total team runs
int calculateTeamRuns(struct Player team[], int teamSize) {
    int totalRuns = 0;
    for (int i = 0; i < teamSize; i++) {
        totalRuns += team[i].runs1 + team[i].runs2;
    }
    return totalRuns;
}

// Function to display scoreboard
void displayScoreboard(struct Player team[], int teamSize, char *teamName) {
    printf("\nScoreboard for team %s:\n", teamName);
    printf("%-20s %-15s %-15s\n", "Player Name", "1st Innings", "2nd Innings");
    for (int i = 0; i < teamSize; i++) {
        printf("%-20s %-15d %-15d\n", team[i].name, team[i].runs1, team[i].runs2);
    }
}

int main() {
    int teamSize = 11;
    struct Player india[teamSize], Team1[teamSize];

    // Input player data for both teams
    inputPlayerData(india, teamSize, "India");
    inputPlayerData(Team1, teamSize, "Team1");

    // Calculate total runs for both teams
    int totalRunsIndia = calculateTeamRuns(india, teamSize);
    int totalRunsTeam1 = calculateTeamRuns(Team1, teamSize);

    // Display the scoreboards
    displayScoreboard(india, teamSize, "India");
    displayScoreboard(Team1, teamSize, "Team1");

    // Determine and display the result
    printf("\nTotal runs scored by India: %d\n", totalRunsIndia);
    printf("Total runs scored by Team1: %d\n", totalRunsTeam1);

    if (totalRunsIndia > totalRunsTeam1) {
        printf("India won the match by %d runs.\n", totalRunsIndia - totalRunsTeam1);
    } else if (totalRunsTeam1 > totalRunsIndia) {
        printf("Team1 won the match by %d runs.\n", totalRunsTeam1 - totalRunsIndia);
    } else {
        printf("The match is a draw.\n");
    }

    return 0;
}
