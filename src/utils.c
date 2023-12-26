#include "utils.h"




double cosine(const char* v1, const char* v2) {


	return 0;
}



int equals(char* s1, char* s2) {
	int i = 0;

	while (s1[i] || s2[i]) {
		if(s1[i] != s2[i]) {
			return 0;
		}
		i++;	
	}

	return 1;
}


void split(char* str, char** list) {

	int i=0;
	int j=0;

	list[0] = str;

	while (str[i]) {

		if(str[i] == ' ') {
			str[i] = '\0';
			list[++j] = &str[i+1];
		}

		i++;
	}

	list[++j] = 0;
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

/* https://www.machinelearningplus.com/nlp/cosine-similarity/ */
/* https://towardsdatascience.com/cosine-similarity-how-does-it-measure-the-similarity-maths-behind-and-usage-in-python-50ad30aad7db */

/* https://www.sciencedirect.com/topics/computer-science/cosine-similarity */
/* https://en.wikipedia.org/wiki/Cosine_similarity */
/* https://www.geeksforgeeks.org/cosine-similarity/ */

/* -------------------------- */
