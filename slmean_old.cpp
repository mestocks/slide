
#include <vector>
#include <iostream>
#include <algorithm>

int main(int argc, char *argv[]) {

  size_t winsize = atoi(argv[1]);
  
  std::vector<int> sarray(winsize);

  int pos;
  double value;
  double vmean;
  int n = 1;
  int b = 0;
  int swin = 0;
  int a = 1 - winsize;
  
  while (std::cin >> pos >> value) {

    swin += value;
    if (a >= 0) {
      swin -= sarray[b];
    }

    sarray[b] = value;

    vmean = swin / n;
    std::cout << pos << " " << vmean << std::endl;

    a++;
    b++;
    if (a == winsize) { a = 0; }
    if (b == winsize) { b = 0; }
    if (n != winsize) { n++; }
  }

  return 0;
}
