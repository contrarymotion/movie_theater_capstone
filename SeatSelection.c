#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include <ctype.h>




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
void bookSeats(MYSQL *conn, int numSeats, int movieId) {
   int count = 0;
   printf("Enter the row letter and column number of the seats you want to book.\n");


   while (count < numSeats) {
       char row_char; // Variable to store the row letter as character
       int col;       // Variable to store the column number as integer


       printf("Enter the seat row (A-J): ");
       scanf(" %c", &row_char);
       //row_char = toupper(row_char); // Ensure row_char is uppercase for consistency
       if (row_char < 'A' || row_char > 'J') {
           printf("Invalid row. Please try again.\n");
           continue;
       }


       printf("Enter the column (1-%d): ", COLS);
       scanf(" %d", &col);
       if (col < 1 || col > COLS) {
           printf("Invalid column. Please try again.\n");
           continue;
       }


       // Assuming the database and your application use the same indexing for columns
       if (updateSeatStatus(conn, movieId, row_char, col)) {
           printf("Seat %c%d successfully booked.\n", row_char, col);
           count++;
       } else {
           printf("Seat %c%d is already booked or could not be booked. Please select another seat.\n", row_char, col);
       }
   }
}


