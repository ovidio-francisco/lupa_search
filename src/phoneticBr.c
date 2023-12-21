#include "utils.h"
#include "lupa.h"
#include "phoneticBr.h"

#include <stdio.h>


/* **** MACROS like a functions **** */

#define BETWEEN_VOWELS  ( is_vowel(prev) && is_vowel(next) )
#define NEXT_IS(X,Y) 	( next == (X) || next == (Y) )
#define IS_LAST         ( next == 0   || next == ' '  )

#define REMOVE_NEXTS(X)\
{\
	while (next == (X)) {\
		i += jmp;\
		next = get_clean(text, i, &jmp);\
	}\
}

#define X_TO_Y(X,Y)\
{\
	if (c == (X))\
	{ result[j++] = (Y);\
		continue; \
	}\
}

#define ADD(X)\
{\
	result[j++] = (X);\
	continue;\
}


char* phonBr(char* text, char *result) {
	unsigned char c, next, prev;
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
				
	
		if (c == 'S' ) {

			if (BETWEEN_VOWELS) {
				ADD(_Z)
			}

			REMOVE_NEXTS('C');

			if (next == 'H') {
				REMOVE_NEXTS('H');
				ADD(_X);
			}
		}

		if (c == 'R') {

			if ( BETWEEN_VOWELS ) {
				ADD('r');
			}

			REMOVE_NEXTS('R');

			if (IS_LAST || is_consonant(next)) {      // is the last? Or is next a consonant != 'R'?
				ADD('r');
			}
		}



		/* --- Remove repetitions --- */

		while (c == next) {
			i += jmp;
			next = get_clean(text, i, &jmp);
		}

		/* --- ------------------ --- */

		
		if (c == 'Z') {
			if(next == ' ' || next == 0) {
				ADD(_S);
			}	
		}

		if (c == 'C'  ) {
			if (j == 0 && NEXT_IS('E', 'I')) {
				ADD(_S);
			}
			if (next == 'H') {
				REMOVE_NEXTS('H');
				ADD(_X);
			}
		}

		if (c == 'G') {
			if(NEXT_IS('E','I')) {
				ADD(_J);
			}	
		}

		if (c == 'U') {
			if( (prev == 'Q' || prev == 'G') && NEXT_IS('E','I') ) {
				/* just continue */
				continue;
			}	
		}

		if (c == 'P' && next == 'H') {
			REMOVE_NEXTS('H')
			ADD(_F);
		}

		if (c == 'X') {
			if (next == 'T') {
				ADD(_S);
			}
			if (is_consonant(next)) {    /* just continue */
				continue;
			}
			if (prev == 'E') {
				ADD(_Z);
			}
			if (prev == 'O' || prev == 'U') {
				ADD(_C);
			}
		}

		if (c == 'L') {
			if (next == 'H') {
				REMOVE_NEXTS('H')
				result[j++] = _L; 
				result[j++] = _I; 
				continue;
			}
			if (IS_LAST) {
				ADD(_U);
			}
		}

		if (c == 'N' && next == 'H') {
			REMOVE_NEXTS('H');
			ADD(_NH);
		}

		if (c == 'M' || c == 'N') {
			if (prev == 'A' && IS_LAST) {
				continue;
			}
			if (is_consonant(next) || IS_LAST)
				ADD(_N);
		}

		
		X_TO_Y(_Ç, _S);
		X_TO_Y(_W, _V);
		X_TO_Y(_K, _C);
		X_TO_Y(_Q, _C);
		

		if (c == ' ' && next == 0) {
			/* just continue */
			continue;
		}



		/* --- Add the char --- */

		if (c < 127) {
			result[j++] = c;
		}
	}

	return result;
}

