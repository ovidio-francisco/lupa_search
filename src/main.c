#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lupa.h"
#include "phoneticBr.h"


void test(char text[], size_t len, char* buffer) {
	phonBr(text, len, buffer);
	printf("PhonetcBr = %s\n", buffer);
}

int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	/* char input[200]; */
	char result[200];

/*
 *     printf("Input something: ");
 *     scanf("%[^\n]s", input);
 *     printf("\n");
 * 
 *     clear(input, strlen(input), result);
 *     printf("Input     = %s\n", input);
 *     printf("Cleaned   = %s\n", result);
 *     
 *     phonBr(input, strlen(input), result);
 *     printf("Input     = %s\n", input);
 *     printf("PhonetcBr = %s\n", result);
 * 
 */

	char text[] = "tancredo do do do la";

	test(text, strlen(text), result);


/*
 *     phonBr("Lavínia MeloMelo", 13, result);
 *     printf("PhonetcBr = %s\n", result);
 * 
 * 
 *     phonBr("Lavíania Melo$elo", 14, result);
 *     printf("PhonetcBr = %s\n", result);
 * 
 * 
 *     phonBr("Luís Carrrrrrrvalho$Lixoxabcdefg", 20, result);
 *     printf("PhonetcBr = %s\n", result);
 * 
 *     phonBr("Luís Carvalho$lixoxabcdefgxxxx", 14, result);
 *     printf("PhonetcBr = %s\n", result);
 *     
 *     phonBr("Lavinia MeloMelo", 12, result);
 *     printf("PhonetcBr = %s\n", result);
 * 
 * 
 *     phonBr(text, strlen(text), result);
 *     printf("PhonetcBr = %s\n", result);
 * 
 * 
 *     printf("len = %lu\n", strlen("Lavínia"));
 *     printf("len = %lu\n", strlen("Lavinia"));
 */
}

/* https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/ */


