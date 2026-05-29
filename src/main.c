#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lupa.h"
#include "phoneticBr.h"


int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	char input[200];
	char result[200];

	printf("Input something: ");
	scanf("%[^\n]s", input);
	printf("\n");

	clear(input, strlen(input), result);
	printf("Input     = %s\n", input);
	printf("Cleaned   = %s\n", result);
	
	phonBr(input, result);
	printf("Input     = %s\n", input);
	printf("PhonetcBr = %s\n", result);

}

/* https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/ */


