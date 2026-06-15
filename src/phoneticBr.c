#include "lupa.h"
#include "phoneticBr.h"
#include <stdio.h>

/* **** MACROS like a functions **** */

#define BETWEEN_VOWELS  ( is_vowel(prev) && is_vowel(next) )
#define NEXT_IS(X,Y) 	( next == (X) || next == (Y) )
#define IS_LAST         ( next == 0   || next == ' '  )
#define NEXT2           ( get_clean(text, idx+1, &jmp) )

#define REMOVE_NEXTS(X)\
	while (next == (X)) {\
		idx += jmp;\
		next = get_clean(text, idx, &jmp);\
	}\

#define X_TO_Y(X,Y)\
	if (c == (X)) {\
	    result[j++] = (Y);\
		STEP;\
		continue; \
	}\

#define ADD(X)\
{\
	result[j++] = (X);\
	STEP;\
	continue;\
}

#define STEP \
{\
		prev = c;\
		c    = next;\
		next = get_clean(text, idx, &jmp);\
		idx+=jmp;\
}\

char* phonBr(char* text, int slen, char *result) {
	unsigned char c, next, prev;
	int idx, j, jmp;

	idx=0;
	j=0;
	c=1;

	c = get_clean(text, idx, &jmp);
	idx+=jmp;

	next = get_clean(text, idx, &jmp);
	idx+=jmp;

	/* printf("len=%d\n", slen); */
	while(c) {
		printf("text='%s' c= '%c' idx=%d\n", text, c, idx);


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

			if (IS_LAST || is_consonant(next)) {      
				ADD('r');
			}
		}



		/* --- Remove repetitions --- */

		while (c == next) {
			idx += jmp;
			next = get_clean(text, idx, &jmp);
		}

		/* --- ------------------ --- */

	
		if (c == 'I' && is_consonant(result[j-1]) && (is_consonant(next) || IS_LAST) ) {
			idx += jmp;
			STEP;
			continue;
		}
	

		if (c == 'U') {
			if( (prev == 'Q' || prev == 'G') && NEXT_IS('E','I') ) {
				/* just continue */
				STEP;
				continue;
			}	
		}


		if (c == 'O' ) {
			if (prev == 'A' && IS_LAST) {
				result[j++] = _U; 
				result[j++] = _N; 
				STEP;
				continue;
			}
			if (next == 'E' && NEXT2 == 'S') { 
				REMOVE_NEXTS('E');
				result[j++] = _O; 
				result[j++] = _I; 
				result[j++] = _N; 
				STEP;
				continue;
			}	
		}


		if (c == 'Z') {
			if(next == ' ' || next == 0) {
				ADD(_S);
			}	
		}

		if (c == 'C'  ) {
			if (NEXT_IS('E', 'I')) {
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

		if (c == 'P' && next == 'H') {
			REMOVE_NEXTS('H')
			ADD(_F);
		}

		if (c == 'X') {
			if (next == 'C') {
				continue;
			}
			if (is_consonant(next)) {
				ADD(_S);
			}
			if (prev == 'E') {
				ADD(_Z);
			}
			if (prev == 'O' || prev == 'U') {
				ADD(_S);
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

		if (c == 'M' || c == 'N' ) {
			if (next == 'H') {
				REMOVE_NEXTS('H');
				ADD(_NH);
			}

			if (prev == 'A' && IS_LAST) {
				continue;
			}
			if (prev == 'E' && IS_LAST) {
				result[j++] = _I; 
				result[j++] = _N; 
				continue;
			}
		}

		if (c == 'M' && ( IS_LAST || is_consonant(next))) {
			ADD(_N);
		}

		
		X_TO_Y(_Ç, _S);
		X_TO_Y(_W, _V);
		X_TO_Y(_K, _C);
		X_TO_Y(_Q, _C);
	

		if (c == ' ' && next == 0) {
			/* just continue */
			STEP;
			continue;
		}


		/* --- Add the char --- */

		if (c < 127) {
			result[j++] = c;
		}
		
		STEP;
	}

	// Parei aqui
	// Como saber onde é o fim da String?
	// Fazer track de toda vez que adicionar algo a result?
	// Usando macros
	// Alterar ADD para não dar continue
	// Criar ADD_CONTINUE
	// Meio que encapsular result (e j???)
	/* result[j-1] = 0;  */

	return result;
}




/*
 * The input (args->args[0]) string may not be a C null terminated string,
 *     so, strlen can fails. We need to explicit pass its length.
 */


/*
Vinícius Melo    -- slen=14
Vinícius Melo    -- slen=14
José Miguel Melo -- slen=17
José Miguel Melo -- slen=17
Lavínia MeloMelo -- slen=13
Lavínia MeloMelo -- slen=13
Júlia MeloloMelo -- slen=11
Júlia MeloloMelo -- slen=11
Ísis MelooloMelo -- slen=10
Ísis MelooloMelo -- slen=10
Lívia MeloloMelo -- slen=11
Lívia MeloloMelo -- slen=11
Lavínia MeloMelo -- slen=13
Lavínia MeloMelo -- slen=13
João Felipe Melo -- slen=17
João Felipe Melo -- slen=17
Théo Melope Melo -- slen=10
Théo Melope Melo -- slen=10
Ísis Melope Melo -- slen=10
Ísis Melope Melo -- slen=10
Antônio MeloMelo -- slen=13
Antônio MeloMelo -- slen=13

bug aqui mesmo?
estaria mariadb correta?

testar no main
*/



/*
 * static inline void add(char** text, int* j, char c) {
 *     (*text)[(*j)++] = c;
 * }
 */
