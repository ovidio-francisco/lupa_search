#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "lupa.h"


#include <stdio.h>

#define MAX_CHARS 16777216 // 2^24 

static char* accenteds   = EXTENDED;
static char* unaccenteds = REDUCED;

static char vowels[]     = VOWELS;
static char consonants[] = CONSONANTS;
static char numbers[]    = NUMBERS;

static char* valids;
static char* chars_types;




/* --- Some private functions prototypes --- */

static int chain2(unsigned char c1, unsigned char c2);
static int chain3(unsigned char c1, unsigned char c2, unsigned char c3);



/* --- The implementations --- */

double lupa(char* s1, char* s2) {
	return 0;
}


char is_vowel(char c) {
	return chars_types[c] == VOWEL;
}

char is_consonant(char c) {
	return chars_types[c] == CONSONANT;
}

char is_number(char c) {
	return chars_types[c] == NUMBER;
}




char init_chars_types() {
	int start = 0;
	int end = _Z;
	int size = end - start + 1;

	int vowels_size =     sizeof(vowels)/sizeof(vowels[0]);
	int consonants_size = sizeof(consonants)/sizeof(consonants[0]);
	int numbers_size =    sizeof(numbers)/sizeof(numbers[0]);
	
	chars_types = (char*)malloc(size * sizeof(char));

	for(int i=start; i<=end; i++) {
		chars_types[i] = UNKNONW;
	}

	for(int i=0; i<vowels_size; i++) {
		chars_types[vowels[i]] = VOWEL;
	}

	for(int i=0; i<consonants_size; i++) {
		chars_types[consonants[i]] = CONSONANT;
	}

	for(int i=0; i<numbers_size; i++) {
		chars_types[numbers[i]] = NUMBER;
	}

	return 0;
}

char init_valids() {
	valids = (char*)malloc(MAX_CHARS * sizeof(char));

	if(valids == NULL) 
		return 1;		// Failure

	for(int i=0; i<MAX_CHARS; i++) {
		valids[i] = i;
	}

	for(char l='a'; l<='z'; l++) {
		valids[l] = l - 32;
	}

	int j=0;
	for(int i=0; i<strlen(accenteds); i++) {
		unsigned char c = accenteds[i];
		int idx;
		
		if (c<=127) {
			idx = c;
			valids[idx] = unaccenteds[j];
		}
		if (c>=192 && c<224) {
			idx = chain2(accenteds[i], accenteds[i+1]);
			valids[idx] = unaccenteds[j];
			i++;
		}
		if (c>=224 && c<240) {
			idx = chain3(accenteds[i], accenteds[i+1], accenteds[i+2]);
			valids[idx] = unaccenteds[j];
			i+=2;
		}
		if (c>=240) {
			i+=3;
		}
		j++;
	}

	return 0;
}


char init() {
	return 
	init_valids() ||
	init_chars_types();
}

char deinit() {
	return 
	deinit_valids() ||
	deinit_char_types();
}

char deinit_valids() {
	if(valids != NULL) {
		free(valids);
		valids = NULL;
	}

	return 0;
}

char deinit_char_types() {
	if(chars_types != NULL) {
		free(chars_types);
		chars_types = NULL;
	}

	return 0;
}

char get_clean(char*s, int i, int* jmp) {
	unsigned char c = s[i];
	unsigned char result = 255;
	int idx;

	if (c<=127) {
		result = valids[c];
		*jmp=1;
	}
	else {
		if (c>=192 && c<224) {
			idx = chain2(s[i], s[i+1]);
			result = valids[idx];
			*jmp=2;
		}  
		else {
			if (c>=224 && c<240) {
				idx = chain3(s[i], s[i+1], s[i+2]);
				result = valids[idx];
				*jmp=3;
			}
		}
	}

	return result;
}



// TODO: rever o clear e o trim.

char* clear(char* s, char* d) {

	int i=0, j=0, jmp=0;
	unsigned char valid;

	do {
		jmp=0;
		valid = 255;

		valid = get_clean(s, i, &jmp);

		if (valid <= 127) {
			i+=jmp;
			if (valid == d[j-1]) {
				continue;
			}
			
			d[j++] = valid;
		} 
		else {
			do {
				d[j++] = s[i++];
			}while((unsigned char)s[i] >= 127 && (unsigned char)s[i] < 192);
		}

	} while(s[i]);
		

	d[j] = 0;

	d = trim(d, j);

	return d;
} 



static int chain2(unsigned char c1, unsigned char c2) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	
	return result;
}


static int chain3(unsigned char c1, unsigned char c2, unsigned char c3) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	result = result << 8;
	result = result | c3;
	
	return result;
}




