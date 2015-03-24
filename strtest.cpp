
#include <vector>
#include <iostream>
#include <algorithm>

class CircularArray {
  
public:

  int a;
  int b;
  int n;
  int winsize;
  std::vector<double> array;
  
  CircularArray(int);

  template <typename Type>
  
  void bump(Type new_value) {

    if (n != winsize) { n++; }
    
    a++;
    b++;
    if (a == winsize) { a = 0; }
    if (b == winsize) { b = 0; }
    
    array[b] = new_value;


  }

  //template <typename Type>
  
  double first() {
    double value;
    if (a >= 0) {
      value = array[a];
    } else {
      value = 0;
    }
    return value;
  }

  //template <typename Type>
  
  double last() {
    return array[b];
  }
};
  
CircularArray::CircularArray(int window_size) {

  winsize = window_size;
  a = 0 - winsize;
  b = -1;
  n = 0;
  
  for (int i = 0; i < winsize; i++) array.push_back(0);
}


int main() {

  int lwin = 4;
  CircularArray oarray(lwin);

  double a;
  double sum = 0;

  while (std::cin >> a) {

    oarray.bump(a);
    sum += oarray.last() - oarray.first();

    if (oarray.n == lwin) {
      std::cout << sum / oarray.n << std::endl;
    }
    
  }
  return 0;
}
