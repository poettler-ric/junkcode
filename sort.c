#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 2

int main(int argc, char **argv) {
    char toParse[] = "34 32 5646 7672 231 346 23 1 6 3 213 54 92 921";
    char delimiters[] = " ";
    char *token;

    int size = INITIAL_SIZE;
    int *integers = malloc(sizeof(int) * size);
    int stored = 0;

    int i;
    int tmp;
    int swaped = 1;

    if (integers == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    // parse the numbers
    token = strtok(toParse, delimiters);
    while (token != NULL) {
        i = strtol(token, NULL, 10);

        // store the integer
        if (stored == size) {
            size *= 2;
            integers = realloc(integers, sizeof(int) * size);

            if (integers == NULL) {
                fprintf(stderr, "realloc failed\n");
                return EXIT_FAILURE;
            }
        }
        *(integers + stored++) = i;

        token = strtok(NULL, delimiters);
    }

    // print the unsorted numbers
    printf("*** unsorted ***\n");
    for (i = 0; i < stored; i++) {
        printf("%d\n", *(integers + i));
    }

    // sort the integers
    while (swaped) {
        swaped = 0;
        for (i = 1; i < stored; i++) {
            // if the first integer is bigger than the second -> swap them
            if (*(integers + i - 1) > *(integers + i)) {
                tmp = *(integers + i - 1);
                *(integers + i - 1) = *(integers + i);
                *(integers + i) = tmp;
                swaped = 1;
            }
        }
    }
    // print the sorted numbers
    printf("*** sorted ***\n");
    for (i = 0; i < stored; i++) {
        printf("%d\n", *(integers + i));
    }

    // freeing memory
    free(integers);

    return (EXIT_SUCCESS);
}
