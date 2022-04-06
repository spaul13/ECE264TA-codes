#include <stdio.h>  
#include <stdlib.h> 

int func(int n){
  printf("Function call\n");
  if(n <= 1){
    return n;
  }
  else{
    return func(n-1) + func(n-2);
  }
}

int main(int argc, char * * argv){
  if(argc != 2){
    printf("Wrong number of input.\n");
    return EXIT_FAILURE;
  }
  int n = (int) strtol(argv[1], NULL, 10);
  printf("func(%d) = %d\n", n, func(n));
  return EXIT_SUCCESS;
}
