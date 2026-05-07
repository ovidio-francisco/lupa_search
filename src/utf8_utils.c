#include "utf8_utils.h"


int chain2(unsigned char c1, unsigned char c2) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	
	return result;
}


int chain3(unsigned char c1, unsigned char c2, unsigned char c3) {
	int result = c1;

	result = result << 8;
	result = result | c2;
	result = result << 8;
	result = result | c3;
	
	return result;
}




