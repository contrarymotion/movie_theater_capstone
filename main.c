#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include "calculate.h"
#include "SeatSelection.h"

#define ROWS 10 
#define COLS 10 

// void initializeSeats(char seats[][COLS]);
// void displaySeats(char seats[][COLS]);
// void bookSeats(char seats[][COLS], int numSeats);

int main() {
    // int totalSeats = ROWS * COLS;
    // char seats[ROWS][COLS];

    MYSQL *conn = initializeConnection();

    // Error message if it fails to connect
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to database.\n");
        return 1;
    }

    // Greet and ask the user to enter the movie they want to watch
    char movieName[50];
    printf("Welcome to the Capstone Theater!\n");
    printf("Enter the movie name: ");
    scanf(" %[^\n]%*c", movieName);

    // Ask the user how many seats they want
    int numSeats;
    int totalSeats = ROWS * COLS;
    printf("How many seats would you like to purchase? ");
    scanf("%d", &numSeats);
        if (numSeats > totalSeats) {
            printf("Sorry, we don't have enough seats available.\n");
            return 1;
        }

    // Get ticket price from database
    float ticketPrice = getTicketPrice(conn, movieName);
        // Error message if price is not found in database
        if (ticketPrice == -1) {
            fprintf(stderr, "Movie not found or price not available.\n");
            closeConnection(conn);
            return 1;
        }

    // Initialize seats for 2-D array seat map
    char seats[ROWS][COLS];
    initializeSeats(seats);

    // Print Seat Map
    printf("Seat selection in progress...\n");
    displaySeats(seats);
    bookSeats(seats, numSeats);

    // Confirm that the seats were booked
    // Need to add code to tell database that certain seats are now occupied
    printf("\nSeats booked successfully!\n");
    displaySeats(seats);

    // ORIGINAL Total cost calculation
    float totalCost = calculateTotalCost(numSeats, ticketPrice);

    // Calculate discounts if any
    // Prompt user if they'd like to use a discount
    /*
    float calculateTotalCost(int numSeats, float ticket, float discount) {
        float totalCost = numSeats * ticketPrice * (1 - discount);
        return totalCost;
    }
    */
    
    // Print receipt for the transaction
    printf("\nReceipt:\n");
    printf("Movie: %s\n", movieName);
    printf("Ticket Price: $%.2f\n", ticketPrice);
    printf("Number of Seats: %d\n", numSeats);
    printf("Total Cost: $%.2f\n", totalCost);

    closeConnection(conn);

    return 0;
}

// printf("We have a total of %d seats.\n", totalSeats);

