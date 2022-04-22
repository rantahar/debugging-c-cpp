#include <stdio.h>
#include <stdlib.h>

void * allocate_one_integer(){
    /* Allocates space for an integer */
    void *pointer = NULL;
    malloc(sizeof(int));
    return pointer;
}

int main(){
    int * pointer = allocate_one_integer();
    *pointer = 4;
    printf("the number is %d\n", *pointer);

    free(pointer);
    return 0;
}
