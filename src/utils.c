#include "utils.h"


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


