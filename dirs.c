#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
	DIR *dir = opendir(".");
	struct dirent *current;

	if (dir == NULL) {
		fprintf(stderr, "couldn't open directory\n");
		return EXIT_FAILURE;
	}

	while ((current = readdir(dir)) != NULL) {
		switch (current->d_type) {
			case DT_DIR:
				printf("dir:\t");
				break;
			case DT_REG:
				printf("file:\t");
				break;
			case DT_LNK:
				printf("link:\t");
				break;
			otherwise:
				printf("other:\t");
				break;
		}
		printf("%s\n", current->d_name);
	}

	closedir(dir);

	return EXIT_SUCCESS;
}
