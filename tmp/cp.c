#include <stdio.h>
#include <string.h>


void cp(char* s, char* d) {
	int t = strlen(s);

	int i;
	for(i=0; i<t; i++) {
		d[i] = s[i];
	}
	d[i]=0;
}


int main() {
	
	printf("\n\n--- Copy ---\n\n\n");

	char* str1 = "abcde";
	int t = strlen(str1);
	char  str2[t];

	cp(str1, str2);

	printf("str2 = %s\n", str2);

}
