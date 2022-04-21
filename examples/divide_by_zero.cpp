#include<iostream>
#include<vector>


template<typename T>
float average(std::vector<T> &vector, int n) {
  T sum = 0;
  for(int i=n; i<vector.size(); i++){
    sum += vector[i];
  }
  int len = vector.size()-n;
  if(len == 0) {
    throw std::runtime_error("Divide by zero in the average-function");
  }
  return sum/(float)len;
}

int main(){
    const int N = 5;
    std::vector<float> vector = {1, 2, 3, 4, 5};
    for(int i=0; i<=N; i++){
        average(vector, i);
    }
    return 0;
}
