#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "test.h"


int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();


	/* char* str = "€pâ ai helo aa❤️ ℤ😻"; */
	/* char* str = "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"; */


	/* char* str1  = "á€€pâÁ àái helo aa❤️ ℤrí😻"; */
	char* original = "€ℤ";
	char* expected = "EZ";
	char  result[strlen(original)];
	clean(original, result);

	int c = test(strcmp(expected, result) == 0, "Symbols to letters");

	printf("Original  = %s\n", original);
	printf("Result    = %s\n", result);
	printf("Expected  = %s\n", expected);
	
	printf("test = %d\n",c);

	test_clean(original, expected);

}

