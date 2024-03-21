#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include <ctype.h>

// 100 seats per seat map
#define ROWS 10
#define COLS 10

// Initialize seats in 2-D array called "seats" in main function
void initializeSeats(char arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = 'O'; // 0 represents an available seat
        }
    }
}

// Print 2-D array called "seats" in main function
void displaySeats(char arr[ROWS][COLS]) {
    printf("    ");
    for (int j = 0; j < COLS; j++) {
        printf("%d ", j + 1); // Print column numbers
    }
    printf("\n");
    printf("    ");
    for (int j = 0; j < COLS; j++) {
        printf("- "); 
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%c | ", 'A' + i); // Print row letters
        for (int j = 0; j < COLS; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

void bookSeats(MYSQL *conn, int numSeats, int movieId) {
   int count = 0;
   printf("\nEnter the row letter and column number of the seats you want to book.\n");

    while (count < numSeats) {
        char row_char; 
        int col;       
        
        // Input Validation
        printf("Enter the seat (e.g., A3): ");
        if (scanf(" %c%d", &row_char, &col) != 2) {
            printf("Invalid input format. Please enter in the format 'RowColumn' (e.g., A3).\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;
        }

        // Convert row_char to uppercase for consistency
        row_char = toupper(row_char);

        if (row_char < 'A' || row_char > 'J' || col < 1 || col > COLS) {
            printf("Invalid seat. Please try again.\n");
            continue;
        }

        // Update seat status
        if (updateSeatStatus(conn, movieId, row_char, col)) {
            printf("Seat %c%d successfully booked.\n", row_char, col);
            count++;
        } else {
            printf("Seat %c%d is already booked or could not be booked. Please select another seat.\n", row_char, col);
        }
    }
}