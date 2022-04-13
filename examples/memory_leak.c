#include <stdio.h>
#include <stdlib.h>

int memory_fail(int i){
    void *lost_pointer;
    lost_pointer = malloc(10*sizeof(int));
    return i+1;
}

int main(){
    int i=5;
    i = memory_fail(i);
    return 0;
}
