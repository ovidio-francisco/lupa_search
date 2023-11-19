#include "lupa_in_mysql.h"
#include "lupa.h"
#include "phoneticBr.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char *output_text;


char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	char *input_text = args->args[0];
	int len = strlen(input_text);

	clear(input_text, output_text);

	initid->ptr = (char*)output_text;
	*length = len;

	output_text[1] = 'H'; // Just for test if it make any change.

	return output_text;
}


char *lupa_phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	char *input_text = args->args[0];
	int len = strlen(input_text);

	phonBr(input_text, output_text);

	initid->ptr = (char*)output_text;
	*length = len;

	/* output_text[1] = '!'; // Just for test if it make any change. */

	return output_text;
}





char lupa_phoneticBr_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	return init_data();
}

void lupa_phoneticBr_deinit(UDF_INIT *initid) {
	deinit_data(initid);
}


char lupa_clear_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	return init_data();
}

void lupa_clear_deinit(UDF_INIT *initid) {
	deinit_data(initid);
}




char init_data() {
	if (init() != 0) {  // lupa init
		return 1;       // Failure;
	} 

	if(output_text == NULL) {
		output_text = (char *)malloc((1024) * sizeof(char));

		if(output_text == NULL) {
			return 2; // Failure;
		}
	}

	return 0;
}


void deinit_data(UDF_INIT *initid) {
	if (initid->ptr != NULL) {
		free(initid->ptr);
		initid->ptr = NULL;
	}
	if (output_text != NULL) {
		free(output_text);
		output_text = NULL;
	}

	deinit(); // lupa deinit
}



