#include <stdlib.h>
#include <string.h>
#include "lupa.h"


#define MAX_CHARS 16777216 // 2^24 

static char* accenteds   = EXTENDED;
static char* unaccenteds = REDUCED;

static char* valids;



/* --- Some private functions prototypes --- */

static int chain2(unsigned char c1, unsigned char c2);
static int chain3(unsigned char c1, unsigned char c2, unsigned char c3);



/* --- The implementations --- */

void init() {

	valids = (char*)malloc(MAX_CHARS * sizeof(char));

	if(valids == NULL) {
		exit(EXIT_FAILURE);
	}

	for(int i=0; i<MAX_CHARS; i++) {
		valids[i] = i;
	}

	for(char l='a'; l<'z'; l++) {
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
}

void deinit() {
	if(valids != NULL) {
		free(valids);
		valids = NULL;
	}
}


char* clean(char* s, char* d) {

	int i=0, j=0, jmp=0, idx=0;
	unsigned char c;
	unsigned char valid;

	do {
		c = s[i];
		jmp=0;
		valid = 255;

		if (c<=127) {
			valid = valids[c];
			jmp=1;
		}
		else {
			if (c>=192 && c<224) {
				idx = chain2(s[i], s[i+1]);
				valid = valids[idx];
				jmp=2;
			}  
			else {
				if (c>=224 && c<240) {
					idx = chain3(s[i], s[i+1], s[i+2]);
					valid = valids[idx];
					jmp=3;
				}
			}
		}

		if (valid <= 127) {
			i+=jmp;
			if (j>0 && valid == d[j-1]) {
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


char*  trim(char* str, int end) {

	while(str[end-1] == ' ') {
		end--;
	}

	str[end] = 0;
	
	while(*str == ' ') {
		str++;
	} 

	return str;
}



double lupa(char* s1, char* s2) {
	return 0;
}

void copy(const char* s, char* d, int count) {
	while(count-- && (*d = *s)) {
		s++;
		d++;
	}
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




