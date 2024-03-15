#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#define ROWS 10
#define COLS 10

void initializeSeats(char arr[ROWS][COLS]);
void displaySeats(char arr[ROWS][COLS]);
void bookSeats(char seats[ROWS][COLS], int numSeats);
void mark_seat_taken(MYSQL *conn, char seats[ROWS][COLS], int row, int col);

#endif
