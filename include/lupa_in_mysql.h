#ifndef LUPA_IN_MYSQL_H
#define LUPA_IN_MYSQL_H
#include <mysql.h>


char *lupa_in_mysql(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);
char*  clean_in_mysql(char* s, char* d);

#endif

