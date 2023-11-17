#include "utils.h"
#include "phoneticBr.h"

int idx;
char c;
char* str;

char next() {
	return str[idx];
}

char* phoneticBr(char* text, char *result) {
	copy(text, result);
	return text;
}



