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

int updateSeatStatus(MYSQL *conn, int movieId, char row, int col) {
  char query[1024];
  snprintf(query, sizeof(query),
    "UPDATE seat_map "
    "JOIN movie_map ON seat_map.seat_map_id = movie_map.seat_map_id "
    "SET seat_map.occupied = 1 "
    "WHERE movie_map.movie_id = %d "
    "AND seat_map.seat_row = '%c' "
    "AND seat_map.seat_column = %d "
    "AND seat_map.occupied = 0",
    movieId, row, col);

  // Execute the query
  if (mysql_query(conn, query)) {
      fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
      return 0; // Failure to update the seat status
  }

  if (mysql_affected_rows(conn) == 0) {
      // No rows were updated indicating the seat was already booked or does not exist
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

    printf("Available Movies:\n\n");
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s: %s\n", row[0], row[1]); // Display movie_id and title
    }

    // Ask the user to select a movie by its ID
    int movieId;
    printf("\nEnter the movie ID you want to watch: ");
    scanf("%d", &movieId);

    // Check if the entered movieId is within the valid range (1, 2, or 3)
    while (movieId < 1 || movieId > 3) {
    printf("Invalid input. Please enter a valid movie ID (1, 2, or 3): ");
    // Clear the input buffer before reading again
    while(getchar() != '\n');
    scanf("%d", &movieId);
    }

    mysql_free_result(result);
    return movieId;
}
