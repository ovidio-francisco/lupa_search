#include <stdio.h>
#include "lupa.h"
#include "phoneticBr.h"

int main() {
	printf("--- Debug ---\n\n");

	init();

	char* str = "jjjjooooosssssseeeeéééêêê";
	char str1[100]; 
	phonBr(str, str1);

	printf("Original: %s\n", str);
	printf("Phonetic: %s\n", str1);

	deinit();

}



