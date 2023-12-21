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
	passeds += result;

	if (result) return result;

	printf("Original = '%s'\n", original);
	printf("Result   = '%s'\n", cleaned);
	printf("Expected = '%s'\n", expected);    

	if (result) {
		printf("👍 %s\n\n", msg);
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
	
	passeds += result;

	if (result) return result;


	printf("Original = '%s'\n", original);
	printf("Result   = '%s'\n", phonetic);
	printf("Expected = '%s'\n", expected);    

	if (result) {
		printf("👍 %s\n\n", msg);
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
	/* test_clean(EXTENDED, "AEIOUICZAEIOUIC E", "All exchanges"); */
	/* test_clean("Aí José coração vovô", "AI JOSE CORACAO VOVO", "Basic accents"); */
	test_clean("abcd.efgh@gmail.com", "ABCD EFGH GMAIL COM", "Ponctuation to space"); 
	test_clean("....points.and spaces;;;", "POINTS AND SPACES", "Ponctuation and trim"); 
	test_clean("hhello   worrrrllddd", "HELO WORLD", "Duplicates"); 
	test_clean("   trim   trim  ", "TRIM TRIM", "Trim");
	test_clean("€ℤ", "EZ", "Symbols to letters");
	test_clean("❤️ 😻", "❤️ 😻", "Basic emojis"); 


	test_phonetic("jjjjoooooseeeeéééêêê", "JOZE", "S between vowels → Z");

	test_phonetic("casa",         "CAZA",      "S between vowels → Z");
	test_phonetic("casta",        "CASTA",     "vowel + S + consonant → S");
	test_phonetic("sapo",         "SAPO",      "S at first → S");
	test_phonetic("cassandra",    "CASANDRA",  "S + S → S");
	test_phonetic("nascimento",   "NASIMENTO", "S + S → S");
	test_phonetic("nascccimento", "NASIMENTO", "S + S → S");
	test_phonetic("voraz",        "VOrAS",     "Z at the end → S");
	test_phonetic("vorazzzz",     "VOrAS",     "Z at the end → S");


	test_phonetic("rato",        "RATO",   "R at firts → R");
	test_phonetic("torrada",     "TORADA", "R + R → R");
	test_phonetic("torrrrrrada", "TORADA", "R + R → R");
	test_phonetic("aranha",      "ArA~A",  "R + R → R");
	test_phonetic("torta",       "TOrTA",  "R + R → R");
	test_phonetic("Henri",       "HENRI",  "R + R → R");
	test_phonetic("amarrrr",     "AMAr",   "R + R → R");
	test_phonetic("trator",      "TRATOr", "R at the end → r");

	test_phonetic("gato", "GATO", "G+(aou) → G");
	test_phonetic("guto", "GUTO", "G+(aou) → G");
	test_phonetic("gota", "GOTA", "G+(aou) → G");

	test_phonetic("girafa", "JIrAFA", "G+(aou) → J");
	test_phonetic("gestão", "JESTAO", "G+e → J");
	test_phonetic("jeito",  "JEITO",  "J+e → J");
	test_phonetic("jiló",   "JILO",   "J+i → J");

	test_phonetic("guerra",       "GERA",   "G+UE → G");
	test_phonetic("guuuuuitarra", "GITARA", "G+UI → G");

	test_phonetic("Henriquuuue", "HENRICE", "Q+UE → C");

	test_phonetic("quanto", "CUANTO", "Q+UA → CU");
	test_phonetic("que?",   "CE",     "Q+UE → CE");

	test_phonetic("Será",  "SErA", "^SE → SE");
	test_phonetic("Cesar", "SEZAr", "^CE → SE");
	test_phonetic("Cisão", "SIZAO", "^CE → SE");

	test_phonetic("VALTER", "VALTEr", "V → V");
	test_phonetic("WALTER", "VALTEr", "W → V");

	test_phonetic("FARMÁCIA",     "FArMACIA", "F → F");
	test_phonetic("PHARMÁCIA",    "FArMACIA", "PH → F");
	test_phonetic("PHHHHARMÁCIA", "FArMACIA", "PH → F");

	test_phonetic("Caique", "CAICE", "C → C");
	test_phonetic("KaiKe",  "CAICE", "K → C");

	test_phonetic("lama",    "LAMA", "L+vowel → L");
	test_phonetic("lhama",   "LIAMA", "L+H → L");
	test_phonetic("familia", "FAMILIA", "L+I → LI");
	test_phonetic("familha", "FAMILIA", "L+H → LI");

	test_phonetic("cha",    "XA",    "CH+vowel → X");
	test_phonetic("Sheila", "XEILA", "SH+vowel → X");

	test_phonetic("também", "TANBEN", "M+consonant → N");
	test_phonetic("sente",  "SENTE",  "N+consonant → N");
	test_phonetic("sum",    "SUN",    "N at last → N");

	test_phonetic("caça",   "CASA", "Ç → S");
	test_phonetic("caca",   "CACA", "C → C");

	test_phonetic("romam",  "ROMA", "M at last → removed");
	test_phonetic("roman",  "ROMA", "M at last → removed");

	test_phonetic("mingau", "MINGAU", "U at last → U");
	test_phonetic("sal",    "SAU", "L at last → U");

	test_phonetic("ninho",    "NI~O", "NH → ~");

	test_phonetic("exame",     "EZAME",     "EX → Z");
	test_phonetic("exercício", "EZErCICIO", "EX → Z");
	test_phonetic("xarope",    "XArOPE",    "X at beginning → X");
	test_phonetic("enxame",    "ENXAME",    "X at beginning → X");
	test_phonetic("texto",     "TESTO",     "XT → S");
	test_phonetic("extensão",  "ESTENSAO",  "XT → S");
	test_phonetic("Próximo",   "PROCIMO",   "OX → C");
	test_phonetic("Auxílio",   "AUCILIO",   "UX → C");
	test_phonetic("trouxe",    "TROUCE",    "UX → C");
	test_phonetic("máximo",    "MAXIMO",    "AX → X");
	test_phonetic("abacaxi",   "ABACAXI",   "AX → X");
	test_phonetic("faxina",    "FAXINA",    "AX → X");
	test_phonetic("Alexandre", "ALEZANDRE", "EX → X");

/* abacaxi */
	/* faxina */
	/* Alexandre */


// MN
// SH
// romã e romam
// sal sau
// adivogado
// peneu
// ninho
// fax
// caça cassa
//
//



// Regras do X
/* NA ULTIMA SILABA     = KiS   */
/* EX+ VOGAL = Z    */
/* IX+ VOGAL = X   */
/* OX+ I     = X   */
/* UX+    */



/* X no começo */
/* Xícara */
/* Xarope */
/* Xadrez */
/* Xereta */

/* X sem som */
/* Excesso */
/* Exceto */
/* excelente */


/* X → S */
/* sexto */
/* texto */
/* Extensão */


/* X → S */
/* Próximo */
/* Auxílio */
/* trouxe */
/* maximo */

/* X → KS */
/* Fixo */
/* Tóxico */
/* Mixagem */
/* Complexidade */
/* Nix */
/* Matrix */
/* Fixação */
	
/* Pixote */
/* Elixir */


	deinit();

	printf("\n%d/%d - ", passeds, count);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}

}



