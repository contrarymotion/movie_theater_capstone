#ifndef DATABASE_H
#define DATABASE_H

#include <ctype.h>
#include <mysql/mysql.h>

MYSQL *initializeConnection();
int updateSeatStatus(MYSQL *conn, int movieId, char row, int col);
float getTicketPrice(MYSQL *conn, const char *movieName);
void closeConnection(MYSQL *conn);
int selectMovie(MYSQL *conn);

#endif