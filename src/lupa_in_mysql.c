#include "lupa_in_mysql.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *lupa(UDF_INIT *initid, UDF_ARGS *args, char *result,
                          unsigned long *length, char *is_null, char *error) {

	excecutar o clean do lupa para começar os testes;

	return 0;
}

void lupa_deinit(UDF_INIT *initid) {
  if (initid->ptr != NULL) {
    free(initid->ptr);
    initid->ptr = NULL;
  }
}

char lupa_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  // Perform any necessary setup or initialization here
  return 0;
}
