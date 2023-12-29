#include "lupa_in_mysql.h"
#include "lupa.h"
#include "phoneticBr.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/* #include "utils.h" */
#include "buffers.h"

char *output_text;


double lupa_similarity(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

    if (args->args[0] == NULL || args->args[1] == NULL) {
        *is_null = 1;
        return 0.0;
    }

	/* char  phon1[strlen(args->args[0])]; */
	/* char  phon2[strlen(args->args[1])]; */
	
	/* phonBr(args->args[0], phon1); */
	/* phonBr(args->args[1], phon2); */
	
	/* return cosine(phon1, phon2); */

	return similarity(args->args[0], args->args[1]);
}



char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	char *input_text = args->args[0];

	clear(input_text, output_text);

	initid->ptr = (char*)output_text;
	*length = strlen(output_text);

	return output_text;
}


char *lupa_phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error) {

	char *input_text = args->args[0];

	phonBr(input_text, output_text);

	initid->ptr = (char*)output_text;
	*length = strlen(output_text);

	/* output_text[1] = '!'; // Just for test if it make any change. */

	return output_text;
}




char lupa_similarity_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
	init();
	init_cosine_buffers(100);	

	return 0;
}

void lupa_similarity_deinit(UDF_INIT *initid) {
	deinit_cosine_buffers();
	deinit();
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


/* https://dev.mysql.com/doc/extending-mysql/8.0/en/adding-loadable-function.html */



