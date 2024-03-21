# Use "make" to compile all files for movie_theater app

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -I../include
LIBS = `mysql_config --cflags --libs` -lmysqlclient

SRCS = main.c database.c calculate.c SeatSelection.c
OBJS = $(SRCS:.c=.o)

TARGET = movie_theater

.PHONY: all clean populate_seats

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)	

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@	
	
populate_seats:
	mysql -u root -pstudent seat < populate_seats.sql

clean:
	rm -f $(OBJS) $(TARGET)