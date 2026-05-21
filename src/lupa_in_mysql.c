#include "lupa_in_mysql.h"
#include "lupa.h"
#include "mariadb_com.h"
#include "phoneticBr.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>



char *alloc_output(UDF_INIT *initid, size_t size) {

	free_output(initid);

	initid->ptr = malloc(size);

	return initid->ptr;
}


void free_output(UDF_INIT *initid) {
	if (initid->ptr) {
		free(initid->ptr);
		initid->ptr = NULL;
	}
}


char lupa_similarity_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {

	return 0;
}

void lupa_similarity_deinit(UDF_INIT *initid) {

}


double lupa_similarity(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {

    if (args->args[0] == NULL || args->args[1] == NULL) {
        *is_null = 1;
        return 0.0;
    }

	return similarity(args->args[0], args->args[1]);
}









char lupa_clear_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {

	// Alloc here to thread safetty
	size_t size = args->lengths[0] + 1; // +1 for null terminator
	initid->ptr = alloc_output(initid, size);

	if (!initid->ptr) {
		strcpy(message, "Error on alloc lupa_clear buffer");
		return 1;
	}

	return 0;
}

void lupa_clear_deinit(UDF_INIT *initid) {
	/* deinit_data(); */

	free_output(initid);
}

char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	if(args->args[0] == NULL) {
		*is_null = 1;
		return NULL;
	}

	clear(args->args[0], initid->ptr);
	*length = strlen(initid->ptr);

	return initid->ptr;
}






char lupa_phoneticBr_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	
	size_t size = args->lengths[0] + 1; // +1 for null terminator
	initid->ptr = alloc_output(initid, size);

	if (!initid->ptr) {
		strcpy(message, "Error on alloc lupa_clear buffer");
		return 1;
	}

	return 0;

	/* return init_data(); */
}

void lupa_phoneticBr_deinit(UDF_INIT *initid) {

	/* deinit_data(); */

	free_output(initid);
}

char *lupa_phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	if(args->args[0] == NULL) {
		*is_null = 1;
		return result;
	}

	phonBr(args->args[0], initid->ptr);
	*length = strlen(initid->ptr);

	return initid->ptr;
}











