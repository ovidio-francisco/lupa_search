#ifndef LUPA_IN_MYSQL_H
#define LUPA_IN_MYSQL_H
#include <mysql.h>


char *lupa(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);
char*  clean(char* s, char* d);

#endif

