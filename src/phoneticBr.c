#include "utils.h"
#include "phoneticBr.h"

int idx;
char c;
char* str;

char next() {
	return str[idx];
}

char* phonBr(char* text, char *result) {
    char* t = text;
    char* c = result;
	
	for( ; *t; t++, c++) {

		*c = *t;
	
		if (*t == 's') {
			*c = 'J';
			continue;
		}
	}

	return result;
}



