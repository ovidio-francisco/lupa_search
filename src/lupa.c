#include <string.h>
#include <stdio.h>

#define MAX_CHARS 255

char* accenteds    = "âãäáàêẽëéèîĩïíìôõöóòûũüúùŷỹÿýỳyç";
char* un_accenteds = "aaaaaeeeeeiiiiiooooouuuuuyyyyyyç";
char no_accents [MAX_CHARS];


void init() {

	for(int i=0; i<MAX_CHARS; i++) {
		no_accents[i] = i;
	}

	for(int i=0; i<strlen(accenteds); i++) {
		printf("i=%d, ac=%d char='%c'", i, (unsigned char)accenteds[i], accenteds[i]);
		if ((unsigned char)accenteds[i] == 195) {
			printf(" <--");
		}
		printf("\n");
	}

}



double lupa(char* s1, char* s2) {
	return 0;
}




