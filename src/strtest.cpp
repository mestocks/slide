
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <cmath>

#include <objects.h>

int midpoint( int endpos, int winsize ) { return endpos - std::floor(winsize / 2.0); }

int main() {

  std::string stra;
  double a;
  std::string chr;
  std::string old_chr = "empty";
  int pos;
  int old_pos = -1;

  int lwin = 6;

  // 0 for missing data, 1 for useable data
  CircularArray<int> NAarray(lwin);
  CircularArray<double> oarray(lwin);

  double sum = 0;
  int n = 0;
  int i = 0;

  while (std::cin >> chr >> pos >> stra) {
    
    if (old_chr == "empty") { old_chr = chr; }
    if (old_pos == -1) { old_pos = pos; }

    if (old_chr != chr) {
      NAarray.reset();
      oarray.reset();
      sum = 0;
      n = 0;
      i = 0;
      old_chr = chr;
      old_pos = pos;
    }

    while (old_pos < pos - 1) {
      old_pos++;
      NAarray.bump(0);
      a = 0;
      n += NAarray.new_value;
      n -= NAarray.old_value;
      i++;
      oarray.bump(a);
      sum += oarray.new_value - oarray.old_value;
      if (i >= lwin) {
	std::cout << chr << " " << midpoint(old_pos, lwin) << " " << sum / n << " " << n << std::endl;
      }
    }
      old_pos = pos;

    if (stra == "NA") {
      NAarray.bump(0);
      a = 0;
    } else {
      NAarray.bump(1);
      a = std::stod(stra);
    }
    
    n += NAarray.new_value;
    n -= NAarray.old_value;
    i++;

    oarray.bump(a);
    sum += oarray.new_value - oarray.old_value;

    if (i >= lwin) {
      std::cout << chr << " " << midpoint(pos, lwin) << " " << sum / n << " " << n << std::endl;
    }
  }
  return 0;
}
