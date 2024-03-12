#ifndef SEATSELECTION_H
#define SEATSELECTION_H

#define ROWS 10
#define COLS 10

void initializeSeats(char arr[ROWS][COLS]);
void displaySeats(char arr[ROWS][COLS]);
void bookSeats(char seats[ROWS][COLS], int numSeats);

#endif
