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
	
	i+=jmp;
	j=0;

	for(; c; i+=jmp) {
		
		prev = c;
		c    = next;
		next = get_clean(text, i, &jmp);


		/* --- Rules --- */
				
		/* printf("prev='%c' c='%c' next='%c'\n\n", prev, c, next); */
	
		if (c == 'S' ) {

			if (is_vowel(prev) && is_vowel(next)) {
				result[j++] = _Z;
				continue;
			}
			
			while (next == 'C') {
				i += jmp;
				next = get_clean(text, i, &jmp);
			}

		}

		if (c == 'R') {
			if ( is_vowel(prev) && is_vowel(next) ) {
				result[j++] = 'r';
				continue;
			}

			while (next == 'R') {                                          // remove repetitions to check if it is the last  
				i += jmp;
				next = get_clean(text, i, &jmp);
			}

			if (next == 0 || next == ' ' || is_consonant(next)) {          // is the last? Or is next a consonant != 'R'?
				result[j++] = 'r';
				continue;
			}
		}

		/* --- Remove repetitions --- */

		while (c == next) {
			i += jmp;
			next = get_clean(text, i, &jmp);
		}

		
		if (c == 'Z') {
			if(next == ' ' || next == 0) {
				result[j++] = _S;
				continue;
			}	
		}

		if (c == 'C') {

		}


		/* --- Add the char --- */

		if (c < 127) {
			result[j++] = c;
		}
	}

	return result;
}



