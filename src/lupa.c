#include <string.h>
#include <stdio.h>
#include "lupa.h"


/* #define MAX_CHARS 65535 */
#define MAX_CHARS 16777216

char* accenteds        = "€âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳç";
char* unaccenteds      = "EAAAAAEEEEEIIIIIOOOOOUUUUUYYYYYYC"; 
char* ascii_replaceble = "aeiouy.,:;!@?-";
char* ascii_aimed      = "AEIOUY        ";

char  valids[MAX_CHARS];


void init() {

	for(int i=0; i<MAX_CHARS; i++) {
		valids[i] = i;
	}

	for(int i=0; i<strlen(ascii_replaceble); i++) {
		valids[ascii_replaceble[i]] = ascii_aimed[i];
	}
	
	for(int i=0; i<strlen(accenteds); i++) {
		unsigned char c = accenteds[i];
		int idx;
		
		if (c<=127) {
			idx = c;
			printf("idx = %d, char=%c\n", idx, unaccenteds[i]);
			valids[idx] = unaccenteds[i];
		}
		if (c>=192 && c<224) {
			idx = chain2(accenteds[i], accenteds[i+1]);
			printf("idx = %d, char=%c\n", idx, unaccenteds[i]);
			valids[idx] = unaccenteds[i];
			i++;
		}
		if (c>=224 && c<240) {
			idx = chain3(accenteds[i], accenteds[i+1], accenteds[i+2]);
			printf("idx = %d, char=%c\n", idx, unaccenteds[i]);
			valids[idx] = unaccenteds[i];
			i+=2;
		}
		if (c>=240) {
			i+=3;
		}

	}
}



void clean(char* s, char* d) {
	int t = strlen(s);

	int i=0;
	int j=0;
	unsigned char c;
	int idx=0;

	do {
		c = s[i];

		if (c<=127) {
			idx = c;
			printf("1\n");
		
			printf("--> idx = %d c = %c\n", idx, valids[idx]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
		}

		if (c>=192 && c<224) {
			idx = chain2(s[i], s[i+1]);
			printf("2\n");

	
			printf("--> idx = %d c = %c\n", idx, valids[idx]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
			else {
				d[j++] = s[i];
				d[j++] = s[i+1];
			}
			i++;
	
		}  
		
		if (c>=224 && c<240) {
			idx = chain3(accenteds[i], accenteds[i+1], accenteds[i+2]);
			printf("3\n");


			printf("--> idx = %d c = %c\n", idx, valids[idx]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				printf("Valid %d\n", valid);
				d[j++] = valid;
			}
			else {
				printf("Invalid %d\n", valid);
				d[j++] = s[i];
				d[j++] = s[i+1];
				d[j++] = s[i+2];
			}
			i+=2;
		}

		if (c>=240) {
			printf("4\n");
			/* quando não acha, tem que reconstruir */


			printf("--> idx = %d c = %c\n", idx, valids[idx]);
			unsigned char valid = valids[idx];

			if (valid <= 127) {
				d[j++] = valid;
			}
			else {
				d[j++] = s[i];
				d[j++] = s[i+1];
				d[j++] = s[i+2];
				d[j++] = s[i+3];
			}
			i+=3;
		}



	} while(s[i++]);

	d[j] = 0;
} 



int chain2(unsigned char c1, unsigned char c2) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	
	return result;
}


int chain3(unsigned char c1, unsigned char c2, unsigned char c3) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	result = result << 8;
	result = result | c3;
	
	return result;
}


char unchain(int i, int part) {
	int  mask = 0;
	int  result = 0;

	switch (part) {
		case 0: mask = 0b00000000000000000000000011111111; break;
		case 1: mask = 0b00000000000000001111111100000000; break;
		case 2: mask = 0b00000000111111110000000000000000; break;
		case 3: mask = 0b11111111000000000000000000000000; break;
	}

	result =  i & mask;
	
	switch (part) {
		case 0: ; break;
		case 1: result = result >>  8; break;
		case 2: result = result >> 16; break;
		case 3: result = result >> 24; break;
	}

	return result;
}



double lupa(char* s1, char* s2) {
	return 0;
}




/* ❤️ , ℤ or 😻  */







/* void clean(char* s, char* d) {
 *     int t = strlen(s);
 * 
 *     int i=0;
 *     unsigned char c;
 *     int idx=0;
 * 
 *     do {
 *         c = s[i];
 * 
 *         if (c<=127) {
 *             idx = c;
 *             continue;
 *         }
 * 
 *         if (c>=192 && c<224) {
 *             idx = chain2(s[i], s[i+1]);
 *             i++;
 *             continue;
 *         }
 * 
 *         d[i] = valids[idx];
 * 
 *     } while(s[i++]);
 * 
 *     d[i] = 0;
 * } */






/*     for(int i=0; i<strlen(accenteds); i++) {
 *         unsigned char c = accenteds[i];
 *         printf("d = %u", c);
 *         if (c<=127)          printf("←   1");
 *         if (c>=192 && c<224) printf("<-- 2 %u", chain2(accenteds[i], accenteds[i+1]));
 *         if (c>=224 && c<240) printf("<== 3 %u", chain3(accenteds[i], accenteds[i+1], accenteds[i+2]));
 *         if (c>=240)          printf("<++ 4");
 *         printf("\n");
 * 
 *         valids[c] = unaccenteds[i];
 *     } */







	/* for(int i=0; i<strlen(accenteds); i++) {
	 *     printf("i=%d, ac=%d char='%c'", i, (unsigned char)accenteds[i], accenteds[i]);
	 *     if ((unsigned char)accenteds[i] == 195) {
	 *         printf(" <--");
	 *     }
	 *     printf("\n");
	 * }  */



/* void clean(char* s, char* d) {
 *     int t = strlen(s);
 * 
 *     int i=0;
 * 
 *     do {
 * 
 *         d[i] = valids[s[i]];
 * 
 *     } while(s[i++]);
 * 
 *     d[i] = 0;
 * } */
