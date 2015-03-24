
#include <vector>
#include <iostream>
#include <algorithm>

class CircularArray {

  // Provides a class implementation of a circular array.
  // An array of size 100 can be initialised like this:

  // CircularArray(100) carray;

  // A value can be added like this:

  // carray.bump(4.3)

  // This will update the array, and provide functions to return
  // the new and the bumped value (i.e. the oldest value in the
  // array that will be sacrificed for the new one). 
  
 private:
  int a;
  int b;

  int start() {
    if (a >= 0) {
      return a;
    } else {
      return 0;
    }
  }

  int end() {
    return b;
  }
  
 public:
  int n;
  int winsize;
  double old_value;
  double new_value;
  std::vector<double> array;
  
  CircularArray(int);
  
  double operator [](int index) {
    int p = start();
    if (index < winsize - p) {
      return array[index + p];
    } else {
      return array[index - (winsize - p)];
    }
  }

  template <typename Type>
  
  void bump(Type value) {

    if (n != winsize) { n++; }

    new_value = value;

    if (a >= 0) {
      old_value = array[a];
    } else {
      old_value = 0;
    }
    
    a++;
    b++;
    if (a == winsize) { a = 0; }
    if (b == winsize) { b = 0; }
    
    array[b] = new_value;
  }
};

// constructor
CircularArray::CircularArray(int window_size) {
  
  winsize = window_size;
  a = 0 - winsize;
  b = -1;
  n = 0;
  
  for (int i = 0; i < winsize; i++) { array.push_back(0); }
}
