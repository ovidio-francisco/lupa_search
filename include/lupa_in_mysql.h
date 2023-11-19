#ifndef LUPA_IN_MYSQL_H
#define LUPA_IN_MYSQL_H
#include "lupa.h"
#include <mysql.h>


char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);

char *phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);



// char*  clean_in_mysql(char* s, char* d);

char init_data();
void deinit_data(UDF_INIT *initid);

#endif

