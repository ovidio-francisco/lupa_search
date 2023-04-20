#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "tests.h"

int count = 0;
int passeds = 0;

int test_clean(char* original, char* expected, char* msg) {

	count++;

	char  buffer[strlen(original)];
	char* cleaned = clean(original, buffer);

	int result = strcmp(expected, cleaned) == 0;

	/* printf("Original = '%s'\n", original);
	 * printf("Result   = '%s'\n", cleaned);
	 * printf("Expected = '%s'\n", expected);    */

	if (result) {
		printf("👍 %s\n\n", msg);
		passeds++;
	}
	else {
		printf("❌ %s\n\n", msg);
	}

	return result;
}



int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	test_clean("abcdABCD", "ABCDABCD", "Just ASCII chars");
	test_clean(EXTENDED, "AEIOUICZAEIOUIC E", "All exchanges");
	test_clean("Aí José coração vovô", "AI JOSE CORACAO VOVO", "Basic accents");
	test_clean("abcd.efgh@gmail.com", "ABCD EFGH GMAIL COM", "Ponctuation to space"); 
	test_clean("....points.and spaces;;;", "POINTS AND SPACES", "Ponctuation and trim"); 
	test_clean("hhello   worrrrllddd", "HELO WORLD", "Duplicates"); 
	test_clean("   trim   trim  ", "TRIM TRIM", "Trim");
	test_clean("€ℤ", "EZ", "Symbols to letters");
	test_clean("❤️ 😻", "❤️ 😻", "Basic emojis"); 

	deinit();

	printf("\n%d/%d - ", passeds, count);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}
}



