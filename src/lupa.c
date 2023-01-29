#include <string.h>
#include <stdio.h>
#include "lupa.h"


#define MAX_CHARS 16777216 // 2^24 

static char* accenteds   = ACCENTEDS;
static char* unaccenteds = UNACCENTEDS;

static char  valids[MAX_CHARS];



/* --- Some private functions prototypes --- */

static int chain2(unsigned char c1, unsigned char c2);
static int chain3(unsigned char c1, unsigned char c2, unsigned char c3);



/* --- The implementations --- */

void init() {

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



void clean(char* s, char* d) {

	int i=0, j=0, idx=0;
	unsigned char c;

	do {
		c = s[i];

		if (c<=127) {
			d[j++] = valids[c];
			i++;
			continue;
		}

		if (c>=192 && c<224) {
			idx = chain2(s[i], s[i+1]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
				i+=2;
			}
			else {
				d[j++] = s[i++];
				d[j++] = s[i++];
			}
			continue;
		}  
		
		if (c>=224 && c<240) {
			idx = chain3(s[i], s[i+1], s[i+2]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
			else {
				copy(&s[i], &d[j], 3);
				j+=3;
			}
			i+=3;
			continue;
		}

		if (c>=240) {
			copy(&s[i], &d[j], 4);
			j+=4;
			i+=4;
			continue;
		}

	} while(s[i]);

	d[j] = 0;
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




