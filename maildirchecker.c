#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFERSIZE 1024
#define LENGTH(array) sizeof(array) / sizeof(array[0])

int cutOffChars;

int isNewDir(char *dirName) {
	char *fileName = rindex(dirName, '/');
	if (fileName == NULL) {
		fileName = dirName;
	} else {
		fileName++;
	}
	return strcmp("new", fileName) == 0;
}

void walkDir(char *dirName) {
	DIR *dir = opendir(dirName);
	struct dirent *current;
	char newDirName[BUFFERSIZE];
	char *foundSlash;
	int inNewDir = isNewDir(dirName);
	int newFiles = 0;

	strncpy(newDirName, dirName, LENGTH(newDirName));

	if (dir == NULL) {
		fprintf(stderr, "couldn't open directory %s\n", dirName);
		return;
	}

	while ((current = readdir(dir)) != NULL) {
		if (current->d_type == DT_DIR) {
			if (!strcmp(".", current->d_name)
					|| !strcmp("..", current->d_name)) {
				continue;
			}
			strncat(newDirName,
					"/",
					LENGTH(newDirName));
			strncat(newDirName,
					current->d_name,
					LENGTH(newDirName));
			walkDir(newDirName);
			strncpy(newDirName, dirName, LENGTH(newDirName));
		} else if (current->d_type == DT_REG && inNewDir) {
			newFiles++;
		} else {
			continue;
		}
	}

	if (newFiles && (foundSlash = rindex(dirName, '/')) != NULL) {
		*foundSlash = '\0';
		printf("%s: %d\n", dirName + cutOffChars, newFiles);
	}

	closedir(dir);
}

int main(int argc, char **argv) {
	int i;
	if (argc < 2) {
		fprintf(stderr, "need at least one commandline argument\n");
		return EXIT_FAILURE;
	}
	for (i = 1; i < argc; i++) {
		cutOffChars = strlen(argv[i]) + 1;
		walkDir(argv[i]);
	}

	return EXIT_SUCCESS;
}
