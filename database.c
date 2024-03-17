#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <ctype.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "student"
#define DATABASE "movie_theater"

MYSQL *initializeConnection() {
  MYSQL *conn = mysql_init(NULL);
  if (!conn) { // Check if initialization failed
      fprintf(stderr, "Failed to initialize MySQL connection\n");
      return NULL;
  }
   if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
      fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
      mysql_close(conn); // Close connection before returning NULL
      return NULL;
  }
  return conn;
}

/*
// Query to pull showtimes from showtime table
void showtimes(MYSQL *conn) {
  char query[256];
  printf("List of showtimes:\n");
  snprintf(query, sizeof(query), "SELECT * FROM showtime");

  // if (mysql_query(conn, query)) {
  //     fprintf(stderr, "Failed to load showtimes: %s\n", mysql_error(conn));
  //     return 1; // Return 1 to indicate failure
  // }
  // return 0; // Return 0 to indicate success
} */

int updateSeatStatus(MYSQL *conn, int movieId, char row, int col) {
   char query[1024]; // Ensure your query buffer is large enough
   snprintf(query, sizeof(query),
       "UPDATE seat_map "
       "SET occupied = 1 "
       "WHERE seat_map_id IN ("
           "SELECT * FROM ("
               "SELECT seat_map.seat_map_id "
               "FROM seat_map "
               "JOIN movie_map ON seat_map.seat_map_id = movie_map.seat_map_id "
               "WHERE movie_map.movie_id = %d "
               "AND seat_map.seat_row = '%c' "
               "AND seat_map.seat_column = %d "
               "AND seat_map.occupied = 0"
           ") AS subquery"
       ")", movieId, row, col);
printf("%s\n", query);
   // Execute the query
   if (mysql_query(conn, query)) {
       fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
       return 0; // Failure to update the seat status
   }

   if (mysql_affected_rows(conn) == 0) {
       // No rows were updated, indicating the seat was already booked or does not exist
       return 0;
   }

   return 1; // Successfully updated the seat status
}

float getTicketPrice(MYSQL *conn, const char *movieName) {
  char query[200];
  sprintf(query, "SELECT m.title, p.price FROM movie m JOIN price p ON m.movie_id = p.movie_id WHERE m.title = '%s'", movieName);

  if (mysql_query(conn, query)) {
      fprintf(stderr, "Failed to retrieve ticket prices: %s\n", mysql_error(conn));
      return -1;
  }

  MYSQL_RES *res = mysql_store_result(conn);
  if (!res) { // Check if storing result failed
      fprintf(stderr, "No data returned from query.\n");
      return -1;
  }

  MYSQL_ROW row = mysql_fetch_row(res);
  if (!row) { // Check if fetching row failed
      mysql_free_result(res); // Free result before returning
      return -1;
  }

  float ticketPrice = atof(row[1]);
  mysql_free_result(res);

  return ticketPrice;
}

void closeConnection(MYSQL *conn) {
  mysql_close(conn);
}

int selectMovie(MYSQL *conn) {
   // Query the database for available movies
   if (mysql_query(conn, "SELECT movie_id, title FROM movie")) {
       fprintf(stderr, "%s\n", mysql_error(conn));
       return -1; // Indicate failure
   }

   MYSQL_RES *result = mysql_store_result(conn);
   if (result == NULL) {
       fprintf(stderr, "%s\n", mysql_error(conn));
       return -1;
   }

   printf("Available Movies:\n");
   MYSQL_ROW row;
   while ((row = mysql_fetch_row(result)) != NULL) {
       printf("%s: %s\n", row[0], row[1]); // Display movie_id and title
   }

   // Ask the user to select a movie by its ID
   int movieId;
   printf("Enter the movie ID you want to watch: ");
   scanf("%d", &movieId);

   mysql_free_result(result);
   return movieId;
}
