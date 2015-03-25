
  // Provides a class implementation of a circular array.
  // An array of size 100 can be initialised like this:

  // CircularArray(100) carray;

  // A value can be added like this:

  // carray.bump(4.3)

  // Items in the array can be accessed using indexing:

  // carray[3]

  // These indices are corrected, so that their location in
  // the circular array is hidden. The indices therefore reflect
  // the order in which they are added to the array, with older
  // entries starting at 0, and the most recent entry at position
  // winsize - 1.

template<class Type>
class CircularArray {

 private:
  int a;
  int b;
  int n;
  int winsize;
  std::vector<Type> array;
  int start() { if (a >= 0) { return a; } else { return 0; }}
  int end() { return b; }
  
 public:
  Type old_value;
  Type new_value;
  
  CircularArray(int);
  
  Type operator [](int index) {
    int p = start();
    if (index < winsize - p) {
      return array[index + p];
    } else {
      return array[index - (winsize - p)];
    }
  }


  //template <typename Type>
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

  void reset() {
    a = 0 - winsize;
    b = -1;
    n = 0;
    for (int i = 0; i < winsize; i++) { array[i] = 0; }
  }

  int size() {
    return n;
  }
};

// constructor
template<class Type>
CircularArray<Type>::CircularArray(int window_size) {
  
  winsize = window_size;
  a = 0 - winsize;
  b = -1;
  n = 0;
  
  for (int i = 0; i < winsize; i++) { array.push_back(0); }
}
