#include "lupa_in_mysql.h"
#include "lupa.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *output_text;

char *lupa_in_mysql(UDF_INIT *initid, UDF_ARGS *args, char *result,
                    unsigned long *length, char *is_null, char *error) {

  char *input_text = args->args[0];
  int len = strlen(input_text);

  clean(input_text, output_text);
  /* output_text = input_text; */
  output_text[len] = '\0';
  initid->ptr = (char*)output_text;
  *length = len;

  /* return output_text; */
  return output_text;
}

void lupa_in_mysql_deinit(UDF_INIT *initid) {
  if (initid->ptr != NULL) {
    free(initid->ptr);
    initid->ptr = NULL;
  }
  deinit();
}

char lupa_in_mysql_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
  // Perform any necessary setup or initialization here

  output_text = (char *)malloc((1024) * sizeof(char));

  // todo: esse init aloca algum recurso que precise desalocar?
  init(); // lupa init

  return 0;
}
