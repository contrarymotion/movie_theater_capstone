#include <stdio.h>

// Function to calculate the total cost
float calculateTotalCost(float tickets, float price) {
    return tickets * price;
}

int main() {
    // displays movie details
    char movieName[50];
    float ticketPrice;

    // customer enters number of tickets
    int numTickets;

    // Select movie you want to watch
    printf("Enter the movie name: ");
    scanf("%s", movieName);
    
    // Input the price of the movie
    printf("Enter the ticket price: $");
    scanf("%f", &ticketPrice);

    // Input number of ticket customer wants
    printf("How many tickets would you like to purchase? ");
    scanf("%d", &numTickets);

    // Calculate total cost
    float totalCost = calculateTotalCost(numTickets, ticketPrice);

    // Display receipt
    printf("\nWelcome to the Capstone Theater!\n");
    printf("\nReceipt:\n");
    printf("Movie: %s\n", movieName);
    printf("Ticket Price: $%.2f\n", ticketPrice);
    printf("Number of Tickets: %d\n", numTickets);
    printf("Total Cost: $%.2f\n", totalCost);

    return 0;
}
