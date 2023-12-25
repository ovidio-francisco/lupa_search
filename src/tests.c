#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "phoneticBr.h"
#include "tests.h"
#include "utils.h"

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


int test_the_clean() {

	test_clean("abcdABCD", "ABCDABCD", "Just ASCII chars");
	/* test_clean(EXTENDED, "AEIOUICZAEIOUIC E", "All exchanges"); */
	/* test_clean("Aí José coração vovô", "AI JOSE CORACAO VOVO", "Basic accents"); */
	test_clean("abcd.efgh@gmail.com", "ABCD EFGH GMAIL COM", "Ponctuation to space"); 
	test_clean("....points.and spaces;;;", "POINTS AND SPACES", "Ponctuation and trim"); 
	test_clean("hhello   worrrrllddd", "HELO WORLD", "Duplicates"); 
	test_clean("   trim   trim  ", "TRIM TRIM", "Trim");
	test_clean("€ℤ", "EZ", "Symbols to letters");
	test_clean("❤️ 😻", "❤️ 😻", "Basic emojis"); 

	return 1;
}

int test_the_phonetics() {
	
	test_phonetic("jjjjoooooseeeeéééêêê", "JOZE", "S between vowels → Z");

	test_phonetic("casa",         "CAZA",      "S between vowels → Z");
	test_phonetic("casta",        "CASTA",     "vowel + S + consonant → S");
	test_phonetic("sapo",         "SAPO",      "S at first → S");
	test_phonetic("cassandra",    "CASANDRA",  "S + S → S");
	test_phonetic("nascimento",   "NASMENTO", "S + S → S");
	test_phonetic("nascccimento", "NASMENTO", "S + S → S");
	test_phonetic("voraz",        "VOrAS",     "Z at the end → S");
	test_phonetic("vorazzzz",     "VOrAS",     "Z at the end → S");


	test_phonetic("rato",        "RATO",   "R at firts → R");
	test_phonetic("torrada",     "TORADA", "R + R → R");
	test_phonetic("torrrrrrada", "TORADA", "R + R → R");
	test_phonetic("aranha",      "ArA~A",  "R + R → R");
	test_phonetic("torta",       "TOrTA",  "R + R → R");
	test_phonetic("Henri",       "HENR",  "R + R → R");
	test_phonetic("amarrrr",     "AMAr",   "R + R → R");
	test_phonetic("trator",      "TRATOr", "R at the end → r");

	test_phonetic("gato", "GATO", "G+(aou) → G");
	test_phonetic("guto", "GUTO", "G+(aou) → G");
	test_phonetic("gota", "GOTA", "G+(aou) → G");

	test_phonetic("girafa", "JrAFA",  "G+(aou) → J");
	test_phonetic("gestão", "JESTAO", "G+e → J");
	test_phonetic("jeito",  "JEITO",  "J+e → J");
	test_phonetic("jiló",   "JLO",    "J+i → J");

	test_phonetic("guerra",       "GERA",   "G+UE → G");
	test_phonetic("guuuuuitarra", "GTARA", "G+UI → G");

	test_phonetic("Henriquuuue", "HENRCE", "Q+UE → C");

	test_phonetic("quanto", "CUANTO", "Q+UA → CU");
	test_phonetic("que?",   "CE",     "Q+UE → CE");

	test_phonetic("Será",  "SErA",  "^SE → SE");
	test_phonetic("Cesar", "SEZAr", "^CE → SE");
	test_phonetic("Cisão", "SZAO",  "^CE → SE");

	test_phonetic("VALTER", "VALTEr", "V → V");
	test_phonetic("WALTER", "VALTEr", "W → V");

	test_phonetic("FARMÁCIA",     "FArMASIA", "F → F");
	test_phonetic("PHARMÁCIA",    "FArMASIA", "PH → F");
	test_phonetic("PHHHHARMÁCIA", "FArMASIA", "PH → F");

	test_phonetic("Caique", "CAICE", "C → C");
	test_phonetic("KaiKe",  "CAICE", "K → C");

	test_phonetic("lama",    "LAMA",   "L+vowel → L");
	test_phonetic("lhama",   "LIAMA",  "L+H → L");
	test_phonetic("familia", "FAMLIA", "L+I → LI");
	test_phonetic("familha", "FAMLIA", "L+H → LI");

	test_phonetic("cha",    "XA",    "CH+vowel → X");
	test_phonetic("Sheila", "XEILA", "SH+vowel → X");


	test_phonetic("também", "TANBEIN", "M+consonant → N");
	test_phonetic("sente",  "SENTE",   "N+consonant → N");
	test_phonetic("sum",    "SUN",     "N at last → N");

	test_phonetic("caça",   "CASA",  "Ç → S");
	test_phonetic("caca",   "CACA",  "C → C");

	test_phonetic("romam",  "ROMA",  "M at last → removed");
	test_phonetic("roman",  "ROMA",  "M at last → removed");

	test_phonetic("mingau", "MNGAU", "U at last → U");
	test_phonetic("sal",    "SAU",   "L at last → U");

	test_phonetic("ninho",  "N~O",   "NH → ~");

	test_phonetic("exame",     "EZAME",     "EX → Z");
	test_phonetic("exercício", "EZErSSIO",  "EX → Z");
	test_phonetic("exumação",  "EZUMASAO",  "EX → Z");
	test_phonetic("exilado",   "EZLADO",    "EX → Z");
	test_phonetic("xarope",    "XArOPE",    "X at beginning → X");
	test_phonetic("enxame",    "ENXAME",    "XA → XA");
	test_phonetic("texto",     "TESTO",     "XT → S");
	test_phonetic("extensão",  "ESTENSAO",  "XT → S");
	test_phonetic("Próximo",   "PROSMO",    "OX → C");
	test_phonetic("Auxílio",   "AUSLIO",    "UX → C");
	test_phonetic("trouxe",    "TROUSE",    "UX → C");
	test_phonetic("máximo",    "MAXMO",     "AX → X");
	test_phonetic("abacaxi",   "ABACAX",    "AX → X");
	test_phonetic("abacachi",  "ABACAX",    "CH → X");
	test_phonetic("faxina",    "FAXNA",     "AX → X");
	test_phonetic("Alexandre", "ALEZANDRE", "EX → X");
	test_phonetic("Pixote",    "PXOTE",     "IX → IX");
	test_phonetic("Elixir",    "ELXr",      "IX → IX");

	test_phonetic("Excesso",   "ESESO",    "XC → S");
	test_phonetic("Exceto",    "ESETO",    "XC → S");
	test_phonetic("Excelente", "ESELENTE", "XC → S");
	test_phonetic("sexto",     "SESTO",    "X+consonant → S");
	test_phonetic("texto",     "TESTO",    "X+consonant → S");
	test_phonetic("extensão",  "ESTENSAO", "X+consonant → S");

	test_phonetic("advogado", "ADVOGADO", "D mute → D");
	test_phonetic("pneu",     "PNEU",     "P mute → P");
	test_phonetic("vietnã",   "VIETNA",   "V mute → V");

	test_phonetic("também", "TANBEIN", "M+consonant → N");


	test_phonetic("Xavier xylografou uma xilogravura com extremo zelo.", 
				  "XAVIEr XLOGRAFOU UMA XLOGRAVUrA CON ESTREMO ZELO", "");
	test_phonetic("O xenófobo estava perplexo com a xenofobia que presenciou.", 
				  "O XENOFOBO ESTAVA PErPLEZO CON A XENOFOBIA CE PREZENSIOU", "");
	test_phonetic("O xylophonista entrou no jazz com um solo de xylophone surpreendente.", 
				  "O XLOFONSTA ENTROU NO JAS CON UN SOLO DE XLOFONE SUrPRENDENTE", "");
	test_phonetic("A chef preparou uma pho vietnamita que conquistou todos os paladares.", 
				  "A XEF PREPArOU UMA FO VIETNAMTA CE CONCSTOU TODOS OS PALADArES", "");
	test_phonetic("O xamã Natan realizou um ritual místico na choupana da floresta.", 
				  "O XAMA NATA REALZOU UN RTUAU MSTCO NA XOUPANA DA FLOrESTA", "");



/*
 * X → KS
 * Fixo
 * Tóxico
 * Mixagem
 * Complexidade
 * Nix
 * Matrix
 * Fixação
 */

	return 1;
}

int test_the_cosine() {

	char* list[100];

	char str[100] = "Ovídio José Francisco";

	split(str, list);

	int i=0;

	while(list[i]) {
		/* printf("i=%d\n", i); */
		printf("[%s]\n", list[i]);
		i++;
	}

	return 1;
}


int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n\n");

	init();

	/* test_the_clean(); */
	/* test_the_phonetics(); */

	test_the_cosine();

	deinit();

	printf("\n%d/%d - ", passeds, count);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}

}



