#include <stdio.h>
#include <string.h>
#include "lupa.h"
#include "phoneticBr.h"
#include "tests.h"
#include "utils.h"
#include "buffers.h"

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
	test_phonetic("gestão", "JESTAUN", "G+e → J");
	test_phonetic("jeito",  "JEITO",  "J+e → J");
	test_phonetic("jiló",   "JLO",    "J+i → J");

	test_phonetic("guerra",       "GERA",   "G+UE → G");
	test_phonetic("guuuuuitarra", "GTARA", "G+UI → G");

	test_phonetic("Henriquuuue", "HENRCE", "Q+UE → C");

	test_phonetic("quanto", "CUANTO", "Q+UA → CU");
	test_phonetic("que?",   "CE",     "Q+UE → CE");

	test_phonetic("Será",  "SErA",  "^SE → SE");
	test_phonetic("Cesar", "SEZAr", "^CE → SE");
	test_phonetic("Cisão", "SZAUN",  "^CE → SE");

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
	test_phonetic("exumação",  "EZUMASAUN", "EX → Z");
	test_phonetic("exilado",   "EZLADO",    "EX → Z");
	test_phonetic("xarope",    "XArOPE",    "X at beginning → X");
	test_phonetic("enxame",    "ENXAME",    "XA → XA");
	test_phonetic("texto",     "TESTO",     "XT → S");
	test_phonetic("extensão",  "ESTENSAUN", "XT → S");
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

	test_phonetic("Excesso",   "ESESO",     "XC → S");
	test_phonetic("Exceto",    "ESETO",     "XC → S");
	test_phonetic("Excelente", "ESELENTE",  "XC → S");
	test_phonetic("sexto",     "SESTO",     "X+consonant → S");
	test_phonetic("texto",     "TESTO",     "X+consonant → S");
	test_phonetic("extensão",  "ESTENSAUN", "X+consonant → S");

	test_phonetic("advogado", "ADVOGADO", "D mute → D");
	test_phonetic("pneu",     "PNEU",     "P mute → P");
	test_phonetic("vietnã",   "VIETNA",   "V mute → V");
	test_phonetic("vietnan",  "VIETNA",   "V mute → V");
	test_phonetic("vietnam",  "VIETNA",   "V mute → V");

	test_phonetic("também", "TANBEIN", "M+consonant → N");

	test_phonetic("caminhão",  "CAM~AUN",  "AO  → AUN");
	test_phonetic("caminhaum", "CAM~AUN",  "AUM → AUN");
	test_phonetic("curaçao",   "CUrASAUN", "AO  → AUN");
	test_phonetic("Maomé",     "MAOME",    "AO  → AO");
	test_phonetic("Caos",      "CAOS",     "AO  → AO");


	test_phonetic("corações",     "COrASOINS",   "OES  → OINS");
	test_phonetic("coraçõins",    "COrASOINS",   "OINS → OINS");
	test_phonetic("chapecoenses", "XAPECOENSES", "OE   → AO");
	test_phonetic("coelho",       "COELIO",      "OE   → AO");
	test_phonetic("coerente",     "COErENTE",    "OE   → AO");


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



void test_equal(char* s1, char* s2) {
	count++;
	if(equals(s1, s2)) {
		passeds++;
	}
	else {
		printf("'%s' and '%s' as not equal. But it is.\n", s1,s2);
	}
}

void test_not_equal(char* s1, char* s2) {
	count++;
	if(!equals(s1, s2)) {
		passeds++;
	}
	else {
		printf("'%s' and '%s' as equal. But isn't.\n", s1,s2);
	}
}

void test_the_equals() {

	test_equal("abcde",   "abcde");
	test_equal("ABCDE",   "ABCDE");
	test_equal("abc def", "abc def");
	test_equal("abc def", "abc def");

	test_not_equal("abcde", "abcd" );
	test_not_equal("abcde", "bcde" );
	test_not_equal("bcde",  "abcde");
	test_not_equal("abcd",  "abcde");

}

void test_splited(char* splited, char* expected) {
	count ++;

	if(equals(splited, expected)) {
		passeds++;
	}
	else {
		printf("  Splited: %s\n  Expected: %s\n", splited, expected);
	}
}

int test_splits() {

	char* list[100];
	char str[100] = "Ovídio José Francisco Filho";

	split(str, list);

	test_splited(list[0], "Ovídio");
	test_splited(list[1], "José");
	test_splited(list[2], "Francisco");
	test_splited(list[3], "Filho");


	return 1;
}

void test_cosine(char* s1, char* s2, double expected) {

	count++;

	char str1[100];
	char str2[100];

	strcpy(str1, s1);
	strcpy(str2, s2);


	double result = cosine(str1, str2);
	double diff = result - expected;

	if (diff < 0) diff = -diff;

	if(diff < 0.0001 )
		passeds++;
	else
		printf("Cosine similarity:\n  Expected=%f\n  Calculated: %f\n",
				expected, result);
}

void test_the_cosines() {
	test_cosine(
			"maça banana goiaba goiaba banana", 
			"goiaba uva maça maça", 0.544331);

	/* 
	 * v1 = 1 2 2 0
	 * v2 = 2 0 1 1
	 */

	test_cosine(
			"hello world", 
			"hi world", 0.5);
	test_cosine(
			"Olá mundo!", 
			"Olá mundo!", 1);
	test_cosine(
			"Lógica matemática informação", 
			"gato cachorro", 0);

}


double test_similarities(char* s1, char* s2, double expected) {
	count++;

	double simi = similarity(s1, s2);

	double dif = simi - expected;
	if (dif < 0) dif = -dif;

	if(dif < 0.001) {
		passeds++;
	}
	else {
		printf("Simi between %s & \n%s\n is %f. \n But expected is %f", s1, s2, simi, expected);
	}

	return simi;
}

void test_the_similarities() {
	test_similarities("ovidio", "ovídio josé francisco", 0.577);

	test_similarities("O xamã Natan realizou um ritual místico na choupana da floresta.", 
					  "O chamam Natã realisou um rituau mistico na xoupana da floresta.", 1);

	test_similarities("O campeão de xadrez trocou olhares com o xerife, enquanto a chama das paixões ardia intensamente", 
					  "O campeaum de chadres trocol olhares com o xerife, enquanto a chama das paixoins ardia intençamente", 1);

	test_similarities("Os corações dos leões na imensidão da selva", 
					  "Os coraçoins dos leoins na imensidãum da selva", 1);


}

int main() {

	printf("\n\n--- LUPA, the advanced search ---\n\n");

	init();
	init_cosine_buffers(100);	


	test_the_clean();    
	test_the_phonetics();
	test_splits();       
	test_the_equals();   
	test_the_cosines();
	test_the_similarities();

	deinit_cosine_buffers();
	deinit();

	printf("\n%d/%d - ", passeds, count);

	if (passeds == count) {
		printf("That is what we expected 🚀\n\n");
	}
	else {
		printf("You disappointed me 😟\n\n");
	}

}



