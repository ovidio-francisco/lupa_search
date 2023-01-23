#include <string.h>
#include <stdio.h>
#include "lupa.h"


#define MAX_CHARS 65535

char* accenteds        = "âãäáàêẽëéèîĩïíìôõöóòûũüúùŷỹÿýỳç";
char* unaccenteds      = "AAAAAEEEEEIIIIIOOOOOUUUUUYYYYYC"; 
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
		printf("d = %u", c);
		if (c<=127)          printf("←   1");
		if (c>=192 && c<224) printf("<-- 2 %u", chain2(accenteds[i], accenteds[i+1]));
		if (c>=224 && c<240) printf("<== 3 %u", chain3(accenteds[i], accenteds[i+1], accenteds[i+2]));
		if (c>=240)          printf("<++ 4");
		printf("\n");

		valids[c] = unaccenteds[i];
	}
		
}


void clean(char* s, char* d) {
	int t = strlen(s);

    int i=0;

	do {

		d[i] = valids[s[i]];

    } while(s[i++]);

	d[i] = 0;
}



int chain2(char c1, char c2) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	
	return result;
}

int chain3(char c1, char c2, char c3) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	result = result << 8;
	result = result | c3;
	
	return result;
}




double lupa(char* s1, char* s2) {
	return 0;
}




/* ❤️ , ℤ or 😻  */
















	/* for(int i=0; i<strlen(accenteds); i++) {
	 *     printf("i=%d, ac=%d char='%c'", i, (unsigned char)accenteds[i], accenteds[i]);
	 *     if ((unsigned char)accenteds[i] == 195) {
	 *         printf(" <--");
	 *     }
	 *     printf("\n");
	 * }  */

