/* An example program in C++ that generates a segfault */

#include<iostream>

int * allocate_one_integer() {
  int *p = 0;
  malloc(sizeof(int));
  return 0;
}

int main(){
    int * pointer = allocate_one_integer();
    *pointer = 4;
    std::cout << "the number is " << *pointer << std::endl;
    
    free(pointer);
    return 0;
}

