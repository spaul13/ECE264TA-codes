#include <stdio.h>  
#include <stdbool.h>  

// input: arr is an integer array
// all but one element in arr occur even times
// output: the only integer element that occurs odd times
int findOdd (int * arr, int n) {
    int value = 0;
    int i = 0;
    for (; i < n; i++) {
        value = <--- ANSWER A: fix the code here --->;
    }
    return value;
}

// input: an integer value
// output: false if value is an odd number, else true
bool checkEven (int value) {
    if (value  <--- ANSWER B: fix the code here --->) {
        return false;
    }
    return true;
}

int main(int argc, char * * argv){
    int arr[] = {215, 121, 36, 121, 121, 36, 215, 36, 36};
    int value = findOdd(arr, sizeof(arr)/sizeof(*arr));
    // print in lower-case hexadecimal
    // your answer C should only contain a hexadecimal number
    printf("<--- ANSWER C: %x --->\n", value);
    if(checkEven(value)) {
        printf("%d is an even number.\n", value);
    }
    else {
        printf("%d is an odd number.\n", value);
    }
    return EXIT_SUCCESS;
}
