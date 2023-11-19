#include <stdio.h>
#include "lupa.h"

int main() {
	printf("--- Debug ---\n\n");

	init();
	
	int jmp;
	unsigned char c = get_clean("José.€ℤ❤️  😻", 6, &jmp);
	printf("clean = %c | %d. Jmp = %d\n", c, c, jmp);

	     c = get_clean("José.€ℤ❤️  😻", 9, &jmp);
	printf("clean = %c | %d. Jmp = %d\n", c, c, jmp);

	     c = get_clean("José.€ℤ❤️  😻", 12, &jmp);
	printf("clean = %c | %d. Jmp = %d\n", c, c, jmp);
}
