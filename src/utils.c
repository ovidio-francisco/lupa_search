#include <math.h>
#include "buffers.h"
#include "utils.h"

#include <stdio.h>

void make_frequency_vectors(char* text, int* counts, char** all_tokens, char** sentence_tokens) {
	
	split(text, sentence_tokens);

	int i=0;
	int j=0;

	while(sentence_tokens[i]) {
		j=0;
		while(all_tokens[j]) {
			if (equals(sentence_tokens[i], all_tokens[j])) {
				break;
			}	
			j++;
		}	

		all_tokens[j] = sentence_tokens[i];
		counts[j]++;
	
		i++;
	}
}

double cosine(char* s1, char* s2) {

	clear_cosine_buffers();
	make_frequency_vectors(s1, cosine_counts1, cosine_tokens, cosine_sentence_tokens);
	make_frequency_vectors(s2, cosine_counts2, cosine_tokens, cosine_sentence_tokens);
	
	int    dot   = 0;
	double mag_A = 0;
	double mag_B = 0;

	int i=0;
	while(cosine_tokens[i]) {
		dot   += cosine_counts1[i] * cosine_counts2[i];
		mag_A += cosine_counts1[i] * cosine_counts1[i]; 
		mag_B += cosine_counts2[i] * cosine_counts2[i]; 

		i++;
	}

	return dot / (sqrt(mag_A) * sqrt(mag_B));
}



void split(char* str, char** list) {

	int i=0;
	int j=0;

	list[0] = str;

	while (str[i]) {

		if(str[i] == ' ') {
			/* str[i] = '\0'; */
			list[++j] = &str[i+1];
		}

		i++;
	}

	list[++j] = 0;
}

int equals(char* s1, char* s2) {
	int i = 0;

	/* while (s1[i] || s2[i]) { */

	while ( (s1[i] && s1[i]!=' ') || (s2[i] && s2[i]!=' ') ) {
		if(s1[i] != s2[i]) {
			return 0;
		}
		i++;	
	}

	return 1;
}



char*  trim(char* str, int end) {

	while(str[end-1] == ' ') {
		end--;
	}

	str[end] = 0;
	
	while(*str == ' ') {
		str++;
	} 

	return str;
}


void copy(const char* s, char* d) {
	while((*d = *s)) {
		s++;
		d++;
	}
}



/* ----------COSINE---------- */

/* https://www.omnicalculator.com/math/cosine-similarity */
/* https://tilores.io/cosine-similarity-online-tool */


/* https://www.machinelearningplus.com/nlp/cosine-similarity/ */
/* https://towardsdatascience.com/cosine-similarity-how-does-it-measure-the-similarity-maths-behind-and-usage-in-python-50ad30aad7db */

/* https://www.sciencedirect.com/topics/computer-science/cosine-similarity */
/* https://en.wikipedia.org/wiki/Cosine_similarity */
/* https://www.geeksforgeeks.org/cosine-similarity/ */

/* -------------------------- */



/*     --------- FOR DEBUGS -------
 *
 *     printf("dot = %d\n", dot);
 *     printf("mag_A = %f\n", mag_A);
 *     printf("mag_B = %f\n", mag_B);
 * 
 *     printf("\n");
 *     i=0;
 *     while(l1[i]) {
 *         printf("[%s] == %d\n", l1[i], v1[i]);	
 *         i++;
 *     }
 * 
 *     printf("\n");
 *     i=0;
 *     while(l1[i]) {
 *         printf("[%s] == %d\n", l1[i], v2[i]);	
 *         i++;
 *     }
 * 
 */



