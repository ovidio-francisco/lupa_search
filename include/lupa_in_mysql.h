#ifndef LUPA_IN_MYSQL_H
#define LUPA_IN_MYSQL_H
#include <mysql.h>


// TODO: larger or dynamic allocation based on args->lengths[0].
#define LUPA_OUTPUT_BUFFER_SIZE 1024

char *alloc_output(UDF_INIT *initid, size_t size);
void free_output(UDF_INIT *initid);


char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);

char *phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error);



// char*  clean_in_mysql(char* s, char* d);

char init_data();
void deinit_data();

#endif

