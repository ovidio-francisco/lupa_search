#include "utils.h"
#include "lupa.h"
#include "phoneticBr.h"

#include <stdio.h>

char* phonBr(char* text, char *result) {
	char c, next, prev;
	int i, j, jmp;

	i=0;
	c=127;
	next = get_clean(text, i, &jmp);
	
	for(i=j=0; c; i+=jmp) {
		
		prev = c;
		c    = next;
		next = get_clean(text, i, &jmp);

		while (c == next) {
			i += jmp;
			next = get_clean(text, i, &jmp);
		}
	
		if (c == 'S' && is_vowel(prev) && is_vowel(next)) {
			result[j++] = _Z;
			continue;
		}

		if (c < 127) {
			result[j++] = c;
		}
	}

	return result;
}



