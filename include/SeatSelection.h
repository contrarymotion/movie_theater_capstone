#ifndef SEATSELECTION_H

#define SEATSELECTION_H
#define ROWS 10
#define COLS 10

#include <ctype.h>

typedef struct {
   int movieId;
   char title[256];
   char genre[256];
   char runtime[6]; 
   char rating[11];
   char startTime[6];
   char endTime[6];
} Movie;

typedef struct {
   int seatMapId;
   int mapId; 
   char seatRow;
   int seatColumn;
   int occupied; 
} SeatMap;

typedef struct {
   int movieMapId;
   int movieId;
   int seatMapId;
} MovieMap;

void initializeSeats(char arr[ROWS][COLS]);
void displaySeats(char arr[ROWS][COLS]);
void bookSeats(MYSQL *conn, int numSeats, int movieId);

#endif
