
#include <vector>
#include <iostream>
#include <algorithm>

#include <objects.h>

int main() {

  double a;

  int lwin = 4;
  CircularArray oarray(lwin);

  double sum = 0;

  while (std::cin >> a) {

    oarray.bump(a);
    sum += oarray.new_value - oarray.old_value;

    if (oarray.n == lwin) {

      for (int k = 0; k < oarray.n; k++) {
	std::cout << oarray[k] << " ";
      }
      std::cout << sum / oarray.n << " ";
      std::cout << std::endl;
      
    }
  }
  return 0;
}
