#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lupa.h"




int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();


	/* char* str = "€pâ ai helo aa❤️ ℤ😻"; */
	char* str = "á€€pâÁ àái helo aa❤️ ℤrí😻";
	/* char* str = "âãäáàêẽëéèîĩïíìôõöóòûũüúùyŷỹÿýỳçℤÂÃÄÁÀÊẼËÉÈÎĨÏÍÌÔÕÖÓÒÛŨÜÚÙYŶỸŸÝỲÇ.,:;!@?-€"; */
	int t = strlen(str);
	char str2[t];

	clean(str, str2);
	printf("str = %s\n", str);
	printf("str2= %s\n", str2);
}


