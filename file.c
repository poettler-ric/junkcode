#include <stdio.h>
#include <stdlib.h>

#define LENGTH(array) sizeof(array) / sizeof(array[1])

int main(int argc, char *argv[]) {
	FILE *file = fopen("/etc/passwd", "r");
	char c[1024];
	while (fgets(c, LENGTH(c), file)) {
		printf("%s", c);
	}
	fclose(file);
	return EXIT_SUCCESS;
}
