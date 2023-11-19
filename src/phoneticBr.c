#include "utils.h"
#include "lupa.h"
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
	char dirt;
	
	for( ; *t; t++, c++) {
		*c = *t;
		
		/* dirt = *t; */
		/* *c = get_clean(dirt); */
	
		if (*c == 'S') {
			*c = 'Z';
			continue;
		}

		/* if (dirt>=192 && dirt<224) { */
			/* t++;	 */
		/* } */
			
	}

	return result;
}



