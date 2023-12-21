#include <stdio.h>
#include "lupa.h"
#include "phoneticBr.h"

int main() {
	printf("--- Debug ---\n\n");

	init();

	char* str = "jose.francisco";
	char str1[100]; 

	int jmp=0;
	char clean = get_clean(str, 4, &jmp);
	printf("clean = '%c'\n", clean);

	/* phonBr(str, str1); */

	/* printf("Original: %s\n", str); */
	/* printf("Phonetic: %s\n", str1); */

	deinit();

}



