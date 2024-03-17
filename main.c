#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "database.h"
#include "calculate.h"
#include "SeatSelection.h"
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


  if (mysql_query(conn, "CALL InsertMovieSeatMappings()")) {
   fprintf(stderr, "%s\n", mysql_error(conn));
} else {
   printf("Stored procedure executed successfully.\n");
};


do{
  // Greet and ask the user to enter the movie they want to watch
  printf("Welcome to the Capstone Theater!\n");


int movieId = selectMovie(conn); // Function to display movies and return selected movieId




/*
  // Switch case for main menu (NOT WORKING YET)
  char choice;
      do {
          printf("\n1. Display seating arrangement\n");
          printf("2. Reserve a seat\n");
          printf("3. Exit\n");
          printf("Enter your choice (1-3): ");
          scanf(" %c", &choice);




          switch (choice) {
              case '1':
                  displaySeats(seats, ROWS, COLS);
                  break;
              case '2':
                  bookSeats(char seats[ROWS][COLS], int numSeats);
                  break;
              case '3':
                  printf("Exiting the program.\n");
                  break;
              default:
                  printf("Invalid choice. Please try again.\n");
          }
      } while (choice != '3');
*/




  char movieName[50];
  printf("Enter the movie name: ");
  scanf(" %[^\n]%*c", movieName);




  // Ask what showtime they want for that movie
  // NEED TO REPLACE BOGUS SHOWTIMES WITH REAL ONES IN DATABASE
//    int whichShowtime;
//    printf("Which showtime?\n");
//    printf("1. 3:00 PM\n");
//    printf("2. 6:00 PM\n");
//    printf("3. 9:00 PM\n");
//    printf("Enter your choice (1-3): ");
//    scanf(" %d", &whichShowtime);




//    switch (whichShowtime) {
//        case 1:
//            printf("\nYou picked the 3:00 PM showtime.\n");
//            break;
//        case 2:
//            printf("\nYou picked the 6:00 PM showtime.\n");
//            break;
//        case 3:
//            printf("\nYou picked the 9:00 PM showtime.\n");
//            break;
//        default:
//            printf("\nInvalid choice. Please pick a number between 1 and 3.\n");
//            break;
//        }




  // Ask the user how many seats they want
  int numSeats;
  int totalSeats = ROWS * COLS;
  printf("\nHow many seats would you like to purchase? ");
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
  printf("\nSeat selection in progress...\n");
  displaySeats(seats);
  //bookSeats(MYSQL *conn, char seats[ROWS][COLS], int numSeats, int movieId);
  bookSeats(conn, numSeats, movieId);


  // Confirm that the seats were booked
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
