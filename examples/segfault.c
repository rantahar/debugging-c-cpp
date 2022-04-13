#include <stdio.h>
#include <stdlib.h>

void * get_pointer(){
    void *pointer = 0x0;
    return pointer;
}

int main(){
    int * pointer = get_pointer();
    int number = *pointer;
    return 0;
}
