
#include <vector>
#include <iostream>
#include <algorithm>

#include <pgstats.h>

int main(int argc, char *argv[]) {

  int s;
  int n;
  int N1;
  int N2;
  int pi;
  double tw;
  double tp;
  double tajd;
  
  size_t winsize = atoi(argv[1]);
  std::vector<int> sarray(winsize);
  std::vector<int> parray(winsize);

  int b = 0;
  int swin = 0;
  int pwin = 0;
  int a = 1 - winsize;
  
  while (std::cin >> N1 >> N2) {

    // 

    n = N1 + N2;
    
    if (N1 == 0 || N2 == 0) {
      s = 0;
      pi = 0;
    } else {
      s = 1;
      pi = N1 * N2;
    }

    swin += s;
    pwin += pi;
    if (a >= 0) {
      swin -= sarray[b];
      pwin -= parray[b];
    }

    sarray[b] = s;
    parray[b] = pi;

    tw = wattersons_theta(n, swin);
    tp = tajimas_theta(n, pwin);
    tajd = tajimasD(n, swin, tw, tp);
    
    std::cout << swin << " " << tw << " " << tp << " " << tajd << std::endl;

    a++;
    b++;
    if (a == winsize) { a = 0; }
    if (b == winsize) { b = 0; }
  }

  return 0;
}
