#include <string.h>
#include <stdio.h>
#include "lupa.h"


#define MAX_CHARS 16777216

static char* accenteds   = "€âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳç.,:;!@?-";
static char* unaccenteds = "EAAAAAEEEEEIIIIIOOOOOUUUUUYYYYYYC        "; 

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

	for(int i=0; i<strlen(accenteds); i++) {
		unsigned char c = accenteds[i];
		int idx;
		
		if (c<=127) {
			idx = c;
			valids[idx] = unaccenteds[i];
		}
		if (c>=192 && c<224) {
			idx = chain2(accenteds[i], accenteds[i+1]);
			valids[idx] = unaccenteds[i];
			i++;
		}
		if (c>=224 && c<240) {
			idx = chain3(accenteds[i], accenteds[i+1], accenteds[i+2]);
			valids[idx] = unaccenteds[i];
			i+=2;
		}
		if (c>=240) {
			i+=3;
		}
	}
}



void clean(char* s, char* d) {

	int i=0, j=0, idx=0;
	unsigned char c;

	do {
		c = s[i];

		if (c<=127) {
			d[j++] = valids[c];
			continue;
		}

		if (c>=192 && c<224) {
			idx = chain2(s[i], s[i+1]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
			else {
				d[j++] = s[i];
				d[j++] = s[i+1];
			}
			i++;
			continue;
		}  
		
		if (c>=224 && c<240) {
			idx = chain3(accenteds[i], accenteds[i+1], accenteds[i+2]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
			else {
				d[j++] = s[i];
				d[j++] = s[i+1];
				d[j++] = s[i+2];
			}
			i+=2;
			continue;
		}

		if (c>=240) {
			d[j++] = s[i];
			d[j++] = s[i+1];
			d[j++] = s[i+2];
			d[j++] = s[i+3];

			i+=3;
			continue;
		}

	} while(s[i++]);

	d[j] = 0;
} 


double lupa(char* s1, char* s2) {
	return 0;
}

static int getUTF8(char* s, char* d, int i, int j) {

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




