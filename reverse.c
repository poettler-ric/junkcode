#include <stdio.h>
/*
 * Example function to reverse a string.
 * Source: http://stackoverflow.com/questions/198199/how-do-you-reverse-a-string-in-place-in-c-or-c
 */

void strrev(char *p) {
    char *q = p; // create a pointer to the beginning of the string

    while(q && *q) {
	++q;
    }

    for(--q; p < q; ++p, --q) {
	// XOR-swap (only works if x and y are not identical)
	// x      y
	// 1010 ^ 0011 = 1001 => x
	// 1001 ^ 0011 = 1010 => y
	// 1001 ^ 1010 = 0011 => x
	// 0011   1010
	*p = *p ^ *q;
	*q = *p ^ *q;
	*p = *p ^ *q;
    }
}

int main(int argc, char **argv) {
    do {
	printf("%s ", argv[argc-1]);
	strrev(argv[argc-1]);
	printf("%s\n", argv[argc-1]);
    } while(--argc);

    return 0;
}
