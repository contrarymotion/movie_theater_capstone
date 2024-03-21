#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include "calculate.h"
#include "SeatSelection.h"
#include <string.h>
#include <ctype.h> // Include ctype.h for toupper() function

#define ROWS 10
#define COLS 10

int main() {
    MYSQL *conn = initializeConnection();

    // Error message if it fails to connect
    if (conn == NULL) {
        fprintf(stderr, "Failed to connect to database.\n");
        return 1;
    }

    // Call stored procedure in database
    if (mysql_query(conn, "CALL InsertMovieSeatMappings()")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("======================================\n");
    }

    // Total sales for current session starts at zero
    float totalSales = 0;

    do {
        // Greet and ask the user to enter the movie they want to watch
        printf("Let's get your tickets!\n\n");

        char movieName[50];
        int movieId = selectMovie(conn); // Function to display movies and return selected movieId

        // Hardcoded conditional to assign movieId to movie title
        if (movieId == 1) {
            strcpy(movieName, "Dune: Part Two");
        } else if (movieId == 2) {
            strcpy(movieName, "Forrest Gump");
        } else if (movieId == 3) {
            strcpy(movieName, "Wonka");
        } else {
            printf("Invalid movie ID entered.\n");
            return 1; // Exit the program with an error status
        }

        // Ask the user how many seats they want
        int numSeats;
        int totalSeats = ROWS * COLS;
        // Keep prompting user until valid input is provided
        while (1) {
            printf("\nHow many seats would you like to purchase? ");
            // Validate input
            if (scanf("%d", &numSeats) != 1 || numSeats <= 0) {
                printf("Invalid input. Please enter a positive integer.\n");
                // Clear input buffer
                while (getchar() != '\n');
            } else if (numSeats > totalSeats) {
                printf("Sorry, we don't have enough seats available.\n");
            } else {
                break; // Valid input, exit loop
            }
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
        printf("\nSeat selection in progress...\n");
        displaySeats(seats);
        bookSeats(conn, numSeats, movieId);

        // Confirm that the seats were booked
        printf("\nSeats booked successfully!\n");
        printf("Here's your receipt.\n");

        // Total cost calculation
        float totalCost = calculateTotalCost(numSeats, ticketPrice);

        // Print receipt for the transaction
        printf("========================================\n");
        printf("||  Receipt:                          ||\n");
        printf("    Movie: %s                          \n", movieName);
        printf("||  Ticket Price: $%.2f              ||\n", ticketPrice);
        printf("    Number of Seats: %d                \n", numSeats);
        printf("||  Total Cost: $%.2f                ||\n", totalCost);
        printf("    Thank you for being our guest!     \n");
        printf("========================================\n");

        // Add total cost to total sales for this session
        totalSales += totalCost;

        char choice;
        printf("\nDo you want to purchase more tickets? (y/n): \n");
        scanf(" %c", &choice);
        if (toupper(choice) != 'Y') {
            return 0; // Exit the loop and end the program
        }
    } while (1);

    closeConnection(conn);

    return 0;
}