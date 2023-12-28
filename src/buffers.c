#include <stdlib.h>
#include "buffers.h"

char** cosine_tokens;
char** cosine_sentence_tokens;
int*   cosine_counts1;
int*   cosine_counts2;

int cosine_max_tokens;

void clear_cosine_buffers() {
	for(int i=0; i<cosine_max_tokens; i++) {
		cosine_tokens[i] = NULL;
	}
	for(int i=0; i<cosine_max_tokens/2; i++) {
		cosine_counts1[i] = 0;
	}
	for(int i=0; i<cosine_max_tokens/2; i++) {
		cosine_counts2[i] = 0;
	}
}

char init_cosine_buffers(size_t total_tokens) {
	cosine_max_tokens = total_tokens;

	cosine_tokens  = calloc(total_tokens, sizeof(char*));
	cosine_sentence_tokens = calloc(total_tokens/2, sizeof(char*));
	cosine_counts1 = calloc(total_tokens/2, sizeof(int  ));
	cosine_counts2 = calloc(total_tokens/2, sizeof(int  ));

	if(cosine_sentence_tokens == NULL || cosine_tokens == NULL || cosine_counts1 == NULL || cosine_counts2 == NULL )
		return 1;  

	return 0;
}


char deinit_cosine_buffers() {

	if(cosine_sentence_tokens != NULL) {
		free(cosine_sentence_tokens);
		cosine_sentence_tokens = NULL;
	}

	if(cosine_tokens != NULL) {
		free(cosine_tokens);
		cosine_tokens = NULL;
	}

	if(cosine_counts1 != NULL) {
		free(cosine_counts1);
		cosine_counts1 = NULL;
	}

	if(cosine_counts2 != NULL) {
		free(cosine_counts2);
		cosine_counts2 = NULL;
	}

	return 0;
}



