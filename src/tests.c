#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "tests.h"

int count = 0;
int passeds = 0;

int test_clean(char* original, char* expected, char* msg) {

	count++;

	char  cleaned[strlen(original)];
	reduce(original, cleaned);

	int result = strcmp(expected, cleaned) == 0;

	/* printf("Original = %s\n", original);
	 * printf("Result   = %s\n", cleaned);
	 * printf("Expected = %s\n", expected); */

	if (result) {
		printf("👍 %s : Was passed\n\n", msg);
		passeds++;
	}
	else {
		printf("❌ %s : Something wrong\n\n", msg);
	}

	return result;
}



int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	test_clean(EXTENDED, REDUCED, "All exchanges");
	test_clean("Aí José coração vovô", "AI JOSE CORACAO VOVO", "Basic accents");
	test_clean("€ℤ", "EZ", "Symbols to letters");
	test_clean("❤️ 😻", "❤️ 😻", "Basic emojis");

	printf("\n%d/%d - ", count, passeds);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}


}

