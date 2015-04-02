#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <stdio.h>
#include <string.h>

#include <objects.h>
#include <strparse.h>

void calcmeans(std::istream& input, std::vector<int> columns, int winsize) {

  int a;
  int b;
  int ncols = columns.size();
  std::string line;
  std::vector<double> sums;
  std::vector<CircularArray<double>> carrays;
  
  for (int n = 0; n < ncols; n++) {
    sums.push_back(0);
    CircularArray<double> carray_init(winsize);
    carrays.push_back(carray_init);
  }

  std::string sep = " ";
  while (getline(input, line)) {
    size_t pos = 0;
    int icol = 0;
    int iarray = 0;
    std::string token;
    
    while ((pos = line.find(sep)) != std::string::npos) {
      token = line.substr(0, pos);
      
      if (std::binary_search(columns.begin(), columns.end(), icol)) {
	carrays[iarray].bump(stod(token));
	sums[iarray] += carrays[iarray].new_value - carrays[iarray].old_value;
	//
	std::cout << sums[iarray] / 2 << sep;
	iarray++;
      }
      line.erase(0, pos + sep.length());
      icol++;
    }
    
    token = line.substr(0, pos);
    if (std::binary_search(columns.begin(), columns.end(), icol)) {
      carrays[iarray].bump(stod(token));
      sums[iarray] += carrays[iarray].new_value - carrays[iarray].old_value;
      //
      std::cout << sums[iarray] / 2 << sep;
      iarray++;
    }
    std::cout << std::endl;
  }  
}

int main(int argc, char *argv[]) {

  // ... | slmean [-k 1] -w <int>
  // 1-based
  // [-k 1] [-k 3,4] [-k 3-7] [-k 1,3,5-8,9]
  
  std::map<std::string, int> argtype {
    {"-k", 1}, {"-w", 1}
  };

  std::map<std::string, std::string> argopts {
    {"-k", "1"}, {"-w", "1000"}
  };
  
  argopts = argasso(argc, argv, argtype, argopts);
  
  int winsize = stoi(argopts["-w"]);
  std::string meancols = argopts["-k"];
  std::vector<int> columns = parse_cols(meancols);
  for (int z = 0; z < columns.size(); z++) { columns[z]--; }
  std::sort(columns.begin(), columns.end());
  
  calcmeans(std::cin, columns, winsize);
  
  return 0;
}
