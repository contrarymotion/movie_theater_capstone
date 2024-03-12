#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root" // Replace with your MySQL username
#define PASSWORD "student" // Replace with your MySQL password
#define DATABASE "movie_theater" // Replace with your database name

// Function to calculate the total cost
float calculateTotalCost(float tickets, float price) {
    return tickets * price;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char movieName[50];
    float ticketPrice;
    int numTickets;

    // Initialize connection
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        return 1;
    }

    // Prompt user to enter the movie name
    printf("Enter the movie name: ");
    scanf("%s", movieName);

    // Query database for ticket price
    char query[200];
    sprintf(query, "SELECT price FROM movie WHERE title = '%s'", movieName);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "No data returned from query.\n");
        mysql_close(conn);
        return 1;
    }

    // Retrieve ticket price from the query result
    row = mysql_fetch_row(res);
    if (row == NULL) {
        fprintf(stderr, "Movie not found or price not available.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 1;
    }
    ticketPrice = atof(row[0]);

    mysql_free_result(res);

    // Prompt user to enter number of tickets
    printf("How many tickets would you like to purchase? ");
    scanf("%d", &numTickets);

    // Calculate total cost
    float totalCost = calculateTotalCost(numTickets, ticketPrice);

    // Display receipt
    printf("\nWelcome to the Capstone Theater!\n");
    printf("\nReceipt:\n");
    printf("Movie: %s\n", movieName);
    printf("Ticket Price: $%.2f\n", ticketPrice);
    printf("Number of Tickets: %d\n", numTickets);
    printf("Total Cost: $%.2f\n", totalCost);

    // Close connection
    mysql_close(conn);

    return 0;
}
