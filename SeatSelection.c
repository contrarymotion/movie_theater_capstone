#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
// #include "SeatSelection.h"

#define ROWS 10
#define COLS 10

// Initialize seats in 2-D array called "seats" in main function
void initializeSeats(char arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr[i][j] = 'O'; // Letter 'O' represents an available seat
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
        printf("- "); // Print separator
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
void mark_seat_taken(MYSQL *conn, char seats[ROWS][COLS], char row_char, int col) {
    int row = row_char - 'A';
    if (seats[row][col] == 'X') {
        printf("Seat (%c, %d) is already booked. Please select another seat.\n", 'A' + row_char, col + 1);
        return;
    }
    seats[row][col] = 'X';
    printf("Seat marked as taken.\n");

    // Update the database to mark the seat as occupied
    if (!updateSeatStatus(conn, row_char, col + 1)) {
        fprintf(stderr, "Error updating seat status in database.\n");
    }
} 

void bookSeats(char seats[ROWS][COLS], int numSeats) {
    int count = 0;
    printf("Enter the row letter and column number of the seats you want to book:\n");

    while (count < numSeats) {
        char row_char; // Variable to store the row letter as character
        int row;       // Variable to store the row index as integer
        int col;

        printf("Seat %d: ", count + 1);
        scanf(" %c%d", &row_char, &col); // Corrected format specifier

        // Convert row letter to row index (0-based)
        row = (int)(row_char - 'A'); // Convert uppercase letter to integer index (0-based)

        col = col - 1; // Convert column number to column index (0-based)
      

        // Error message if seat number was typed incorrectly
        if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
            printf("Invalid seat selection. Please select again. Remember to use an uppercase letter.\n");
            continue; // skip this block of code if seat number was typed correctly
        }

        // Error message if seat is already occupied
        if (seats[row][col] == 'X') {
            printf("Seat (%c, %d) is already booked. Please select another seat.\n", 'A' + row, col + 1);
        } else {
            seats[row][col] = 'X'; // 'X' represents a booked seat
            count++; // Increment the count

            // Update the database to mark the seat as occupied
            // updateSeatStatus(conn, row, col); // Assuming 1 represents occupied status
        }
    }
}

