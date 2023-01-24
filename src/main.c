#include <stdio.h>
#include <string.h>
#include "lupa.h"

/* int main() {
 *     double s = lupa("vai", "vai");
 * 
 *     init();
 * 
 *     printf("\n\n--- LUPA, the advanced search ---\n\n\n");
 *     printf("\n\n--- make aaaahah ---\n\n\n");
 *     printf("\n s = %f", s);   
 * 
 * 
 *     for(unsigned char c=32; c<127; c++) {
 *         printf("i= %d, c='%c'\n", c, c);
 *     } 
 *  
 * 
 *     unsigned char str[8];
 *     str[0] = 65;
 *     str[1] = 195;
 *     str[2] = 128;
 * 
 *     printf("--> %s\n", str);
 * 
 * } */


int main() {

	init();



	char* str = "€pâ ai helo aa❤️ℤ😻";
	/* char* str = "€pâ ai helo aa❤️"; */
	/* char* str = "€pâ ai helo aa"; */
	int t = strlen(str);
	char str2[t];

	clean(str, str2);
	printf("str2= %s\n", str2);


	/* for(int c=0; c<127; c++) {
	 *     printf("c = '%c'\n", c);
	 * } */

}


/*
 
 Se o byte > 192 && < 224, então:
	* copia o primeiro byte
	* usa o segundo byte como índice para pegar o caractere válido (que terá 1 byte de tamanho).
 
 */


