#include<iostream>
#include<array>


template<typename T, size_t N>
float average(std::array<T, N> &arr, int n) {
  T sum = 0;
  for(int i=n; i<N; i++){
    sum += arr[i];
  }
  int len = N-n;
  if(len == 0) {
    throw "Divide by zero in the average-function";
  }
  return sum/(float)len;
}

int main(){
    const int N = 5;
    std::array<int, N> array = {1, 2, 3, 4, 5};
    for(int i=0; i<=N; i++){
        average(array, i);
    }
    return 0;
}
