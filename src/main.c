#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lupa.h"




int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	char input[200];
	char result[200];

	printf("Input something: ");
	scanf("%[^\n]s", input);


	clean(input, result);
	printf("\n");
	printf("Input  = %s\n", input);
	printf("Result = %s\n", result);
}


