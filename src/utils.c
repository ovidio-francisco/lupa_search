#include "utils.h"
#include <string.h>

#include <stdio.h>

int split(char* str, char** list) {

	int i=0;
	int j=0;

	list[0] = str;

	while (str[i]) {
		i++;

		if(str[i] == ' ') {
			list[++j] = &str[i+1];
			/* str[i] = '\0'; */
		}
	}

	list[++j] = 0;

	return 0;
}

double cosine(const char* v1, const char* v2) {

/* https://www.machinelearningplus.com/nlp/cosine-similarity/ */
/* https://towardsdatascience.com/cosine-similarity-how-does-it-measure-the-similarity-maths-behind-and-usage-in-python-50ad30aad7db */

/* https://www.sciencedirect.com/topics/computer-science/cosine-similarity */
/* https://en.wikipedia.org/wiki/Cosine_similarity */
/* https://www.geeksforgeeks.org/cosine-similarity/ */

	char str[] = "ovidio jose francisco";

	char* token = strtok(str, " ");

	return 0;
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

