#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "phoneticBr.h"
#include "tests.h"

int count = 0;
int passeds = 0;

int test_clean(char* original, char* expected, char* msg) {

	count++;

	char  buffer[strlen(original)];
	char* cleaned = clear(original, buffer);

	int result = strcmp(expected, cleaned) == 0;

	printf("Original = '%s'\n", original);
	printf("Result   = '%s'\n", cleaned);
	printf("Expected = '%s'\n", expected);    

	if (result) {
		printf("👍 %s\n\n", msg);
		passeds++;
	}
	else {
		printf("❌ %s\n\n", msg);
	}

	return result;
}

int test_phonetic(char* original, char* expected, char* msg) {
	
	count++;

	char  buffer[strlen(original)];
	char* phonetic = phonBr(original, buffer);

	int result = strcmp(expected, phonetic) == 0;

	printf("Original = '%s'\n", original);
	printf("Result   = '%s'\n", phonetic);
	printf("Expected = '%s'\n", expected);    

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


	test_phonetic("jjjjoooooseeeeéééêêê", "JOZE", "S between vowels → Z");
	test_phonetic("casa", "CAZA", "S between vowels → Z");
	test_phonetic("casta", "CASTA", "vowel + S + consonant → S");
	test_phonetic("sapo", "SAPO", "S at first → S");
	test_phonetic("cassandra", "CASANDRA", "S + S → S");
	test_phonetic("nascimento", "NASIMENTO", "S + S → S");
	test_phonetic("nasccccimento", "NASIMENTO", "S + S → S");
	test_phonetic("voraz", "VOrAS", "Z at the end → S");
	test_phonetic("vorazzzz", "VOrAS", "Z at the end → S");


	test_phonetic("rato", "RATO", "R at firts → R");
	test_phonetic("torrada", "TORADA", "R + R → R");
	test_phonetic("torrrrrrada", "TORADA", "R + R → R");
	test_phonetic("aranha", "ArANHA", "R + R → R");
	test_phonetic("torta", "TOrTA", "R + R → R");
	test_phonetic("Henrique", "HENRIQUE", "R + R → R");
	test_phonetic("amarrrr", "AMAr", "R + R → R");
	test_phonetic("trator", "TRATOr", "R at the end → r");

	deinit();

	printf("\n%d/%d - ", passeds, count);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}

}



