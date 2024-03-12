#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>

MYSQL *initializeConnection();
int updateSeatStatus(MYSQL *conn, char row, int col);
float getTicketPrice(MYSQL *conn, const char *movieName);
void closeConnection(MYSQL *conn);

#endif /* DATABASE_H */




