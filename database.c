#include "database.h"
#include <stdio.h> // Include necessary standard headers
#include <stdlib.h>
#include <mysql/mysql.h> // Include MySQL header

#define SERVER "localhost"
#define USER "root" // Replace with your MySQL username
#define PASSWORD "student" // Replace with your MySQL password
#define DATABASE "movie_theater" // Replace with your database name

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

// Query to update the status of a seat, setting occupied to 1 to book
int updateSeatStatus(MYSQL *conn, char row, int col) {
    char query[100];
    snprintf(query, sizeof(query), "UPDATE seat SET occupied = 1 WHERE seat_row = '%c' AND seat_column = %d;", row, col);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to update seat status: %s\n", mysql_error(conn));
        return 0; // Return 0 to indicate failure
    }
    return 1; // Return 1 to indicate success
}

float getTicketPrice(MYSQL *conn, const char *movieName) {
    char query[200];
    sprintf(query, "SELECT m.title, p.price FROM movie m JOIN price p ON m.movie_id = p.movie_id WHERE m.title = '%s'", movieName);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(conn));
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
