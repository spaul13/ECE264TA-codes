#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    int * x = malloc(5 * sizeof(int));
    int * y = malloc(5 * sizeof(int));
    int * * p = &x;
    int * * q = &y;
    
    for (int i = 0; i < 5; i++) {
        x[i] = i;     //x has values [0, 1, 2, 3, 4]
        y[i] = 4 - i; //y has values [4, 3, 2, 1, 0]
    }
    
    printf("* * p = %d\n", * * p); // <=== ANSWER A
    
    printf("* (*q + 1) = %d\n", * (*q + 1)); // <=== ANSWER B

    * q = (*p + 1);
    printf("y[1] = %d\n", y[1]); // <=== ANSWER C
    
    * p = (*q + 1);
    printf("x[1] = %d\n", x[1]); // <=== ANSWER D
    
    return EXIT_SUCCESS;
}
