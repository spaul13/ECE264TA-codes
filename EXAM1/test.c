#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(1) // tell compiler not to pad any space
// assume sizeof(char) = 1, sizeof(a pointer) = 8

int main(int argc, char ** argv)
{
    if (argc < 2) {
        printf("Not enough inputs\n");
        return EXIT_FAILURE;
    }

    char ** arr = malloc((argc-1) * sizeof(char *));
    int i = 0;
    for(; i < argc-1; i++) {
        // strlen(argv[i+1]) computes the length of the
        // string argv[i+1], not including the
        // terminating null character, `\0'.
        arr[i] = malloc((strlen(argv[i+1]) + 1) * sizeof(char));

        // strcpy copies the string pointed to
        // by argv[i+1] to arr[i]
        strcpy(arr[i], argv[i+1]); 
        printf("%s\n", arr[i]);
    }

    for(i = 0; i < argc-1; i++) {
	printf("%s\n",*arr);
        free(arr[i]); // release memory
    }
    // <--- Question A: Fix the following code to release memory --->
    free(**arr);

    return EXIT_SUCCESS;
}
