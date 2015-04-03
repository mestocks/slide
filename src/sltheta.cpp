#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <objects.h>
#include <pgstats.h>

int midpoint( int endpos, int winsize ) {
  return endpos - std::floor(winsize / 2.0);
}

void write( int nchrsites, int winsize, std::string chr, int pos, int nsam, int nsites, int ssum, int psum ) {

  if (nchrsites >= winsize) {

    double tw;
    double tp;
    double tajd;

    if (ssum == 0) {
      tw = 0;
    } else {
      tw = wattersons_theta(nsam, ssum);
    }

    if (psum == 0) {
      tp = 0;
    } else {
      tp = tajimas_theta(nsam, psum);
    }
    
    if (nsites > 0) {
      std::cout << chr << " ";
      std::cout << midpoint(pos, winsize) << " ";
      std::cout << nsam << " " ;
      std::cout << nsites << " ";
      std::cout << ssum << " ";
      std::cout << tw / nsites << " ";
      std::cout << tp / nsites << " ";
      
      if (tw == 0 && tp == 0) {
	std::cout << "NA" << std::endl;
      } else {
	tajd = tajimasD(nsam, ssum, tw, tp);
	std::cout << tajd << std::endl;
      }
      
    } else {
      std::cout << chr << " ";
      std::cout << midpoint(pos, winsize) << " NA ";
      std::cout << nsites << " NA NA NA NA" << std::endl;
    }}
}

int main(int argc, char *argv[]) {

  // ... | slide nsam lwin lstep

  // stdin values
  int pos;
  std::string chr;
  std::string strn1;
  std::string strn2;

  // parameters etc...
  int nsam = atoi(argv[1]);
  int winsize = atoi(argv[2]);
  int lstep = atoi(argv[3]);

  // temporary objects
  int n1;
  int n2;
  int stmp;
  int ptmp;
  int ssum;
  int psum;
  int step;
  int old_pos;
  int nchrsites;
  std::string old_chr;
  CircularArray<int> sarray(winsize);
  CircularArray<int> parray(winsize);
  CircularArray<int> narray(winsize);

  // stdout values (tw, tp & tajd declared in write())
  int ss;
  int nsites;

  // init values
  ssum = 0;
  psum = 0;
  nsites = 0;
  old_pos = -1;
  nchrsites = 0;
  step = 0;
  old_chr = "empty";
  
  while (std::cin >> chr >> pos >> strn1 >> strn2) {
    
    if (old_chr == "empty") { old_chr = chr; }
    if (old_pos == -1) { old_pos = pos; }

    if (old_chr != chr) {
      sarray.reset();
      parray.reset();
      narray.reset();
      ssum = 0;
      psum = 0;
      nsites = 0;
      nchrsites = 0;
      old_chr = chr;
      old_pos = pos;
      step = 0;
    }
    
    while (old_pos < pos - 1) {
      step++;
      old_pos++;
      nchrsites++;
      narray.bump(0);
      sarray.bump(0);
      parray.bump(0);
      ssum += sarray.new_value - sarray.old_value;
      psum += parray.new_value - parray.old_value;
      nsites += narray.new_value - narray.old_value;

      if (step == lstep) {
	write(nchrsites, winsize, chr, old_pos, nsam, nsites, ssum, psum);
	step = 0;
      }
    }
    old_pos = pos;

    if (strn1 == "NA" || strn2 == "NA") {
      narray.bump(0);
      n1 = 0;
      n2 = 0;
    } else {
      n1 = std::stoi(strn1);
      n2 = std::stoi(strn2);
      
      if (n1 + n2 != nsam) {
	narray.bump(0);
	n1 = 0;
	n2 = 0;
      } else {
	narray.bump(1);
      }
    }
    
    if (n1 == 0 || n2 == 0) {
      stmp = 0;
      ptmp = 0;
    } else {
      stmp = 1;
      ptmp = n1 * n2;
    }

    step++;
    nchrsites++;
    
    parray.bump(ptmp);
    sarray.bump(stmp);

    nsites += narray.new_value - narray.old_value;
    ssum += sarray.new_value - sarray.old_value;
    psum += parray.new_value - parray.old_value;

    if (step == lstep) {
      write(nchrsites, winsize, chr, old_pos, nsam, nsites, ssum, psum);
      step = 0;
    }
  }
  return 0;
}
