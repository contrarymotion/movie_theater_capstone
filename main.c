#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <ctype.h> // Include ctype.h for toupper() function
#include "database.h"
#include "calculate.h"
#include "SeatSelection.h"

#define ROWS 10 
#define COLS 10 

int main() {
    MYSQL *conn = initializeConnection();

    // Error message if it fails to connect
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to database.\n");
        return 1;
    }

    char movieName[50];
    int numSeats;

    do {
        // Greet and ask the user to enter the movie they want to watch
        printf("Welcome to the Capstone Theater!\n");
        printf("Enter the movie name: ");
        scanf(" %[^\n]%*c", movieName);

        // Ask the user how many seats they want
        int totalSeats = ROWS * COLS;
        printf("How many seats would you like to purchase? ");
        if (scanf("%d", &numSeats) != 1 || numSeats <= 0) {
            printf("Invalid input. Please enter a valid positive number of seats.\n");
            continue; // Start the loop again for a new transaction
        }
        if (numSeats > totalSeats) {
            printf("Sorry, we don't have enough seats available.\n");
            continue; // Start the loop again for a new transaction
        }

        // Get ticket price from database
        float ticketPrice = getTicketPrice(conn, movieName);
        if (ticketPrice == -1) {
            fprintf(stderr, "Movie not found or price not available.\n");
            continue; // Start the loop again for a new transaction
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

        // Print receipt for the transaction
        printf("\nReceipt:\n");
        printf("Movie: %s\n", movieName);
        printf("Ticket Price: $%.2f\n", ticketPrice);
        printf("Number of Seats: %d\n", numSeats);
        printf("Total Cost: $%.2f\n", totalCost);

        // Ask the user if they want to continue
        char choice;
        printf("\nDo you want to purchase more tickets? (y/n): \n");
        scanf(" %c", &choice);
        if (toupper(choice) != 'Y') {
            break; // Exit the loop and end the program
        }

    } while (1); // Loop indefinitely until the user decides to exit

    closeConnection(conn);
    return 0;
}
