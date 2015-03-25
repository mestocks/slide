
#include <vector>
#include <iostream>
#include <algorithm>

#include <objects.h>

int main() {

  double a;
  std::string chr;
  std::string old_chr = "empty";
  int pos;

  int lwin = 4;
  CircularArray<double> oarray(lwin);

  double sum = 0;

  while (std::cin >> chr >> pos >> a) {
    
    if (old_chr == "empty") { old_chr = chr; }

    if (old_chr != chr) {
      oarray.reset();
      sum = 0;
      old_chr = chr;
    }

    oarray.bump(a);
    sum += oarray.new_value - oarray.old_value;

    if (oarray.size() == lwin) {
      std::cout << chr << " " << pos << " ";
      //for (int k = 0; k < oarray.n; k++) {
      //std::cout << oarray[k] << " ";
      //}
      std::cout << sum / oarray.size() << " ";
      std::cout << std::endl;
      
    }
  }
  return 0;
}
