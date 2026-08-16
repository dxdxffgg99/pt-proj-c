#include "main.h"
#include <stdio.h>

int main(const int argc, char *argv[]){
    printf("Hello World");
    for(int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    return 0;
}