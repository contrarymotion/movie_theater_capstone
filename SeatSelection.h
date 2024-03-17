#ifndef SEATSELECTION_H
#define SEATSELECTION_H


#define ROWS 10
#define COLS 10


#include <ctype.h>


typedef struct {
   int movieId;
   char title[256];
   char genre[256];
   char runtime[6]; // Stored as string to simplify, consider parsing to minutes or a time struct
   char rating[11];
   char startTime[6]; // Similar handling as `runtime`
   char endTime[6];
} Movie;


typedef struct {
   int seatMapId;
   int mapId; // This seems to act as an additional identifier or link to another structure.
   char seatRow;
   int seatColumn;
   int occupied; // Using int for boolean for compatibility with C standards
} SeatMap;


typedef struct {
   int movieMapId;
   int movieId;
   int seatMapId;
} MovieMap;




void initializeSeats(char arr[ROWS][COLS]);
void displaySeats(char arr[ROWS][COLS]);
void bookSeats(MYSQL *conn, int numSeats, int movieId);
//void mark_seat_taken(MYSQL *conn, char seats[ROWS][COLS], int row, int col);


#endif
