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



void calcmeans(std::istream& input,
	       std::vector<int> columns,
	       int winsize,
	       std::string sep = " ") {

  int ncols;
  std::string line;
  std::vector<double> sums;
  std::vector<double> nsums;
  std::vector<CircularArray<int>> narrays;
  std::vector<CircularArray<double>> carrays;

  // Initialise an array containing CircularArrays
  ncols = columns.size();
  for (int n = 0; n < ncols; n++) {
    sums.push_back(0);
    nsums.push_back(0);
    CircularArray<int> narray_init(winsize);
    CircularArray<double> carray_init(winsize);
    narrays.push_back(narray_init);
    carrays.push_back(carray_init);
  }

  int nsites = 0;
  while (getline(input, line)) {

    nsites++;
    
    double item;
    double nitem;
    int icol = 0;
    int iarray = 0;
    size_t pos = 0;
    std::string token;
    
    while ((pos = line.find(sep)) != std::string::npos) {
      token = line.substr(0, pos);
      
      if (std::binary_search(columns.begin(), columns.end(), icol)) {

	if (token == "NA") {
	  item = 0;
	  nitem = 0;
	} else {
	  item = stod(token);
	  nitem = 1;
	}
	carrays[iarray].bump(item);
	narrays[iarray].bump(nitem);
	
	sums[iarray] += carrays[iarray].new_value - carrays[iarray].old_value;
	nsums[iarray] += narrays[iarray].new_value - narrays[iarray].old_value;

	if (nsites >= winsize) {
	  if (nsums[iarray] > 0) {
	    std::cout << sums[iarray] / nsums[iarray] << sep;
	  } else {
	    std::cout << "NA" << sep;
	  }
	}
	iarray++;
      }
      line.erase(0, pos + sep.length());
      icol++;
    }
    
    token = line.substr(0, pos);
      if (std::binary_search(columns.begin(), columns.end(), icol)) {

	if (token == "NA") {
	  item = 0;
	  nitem = 0;
	} else {
	  item = stod(token);
	  nitem = 1;
	}
	carrays[iarray].bump(item);
	narrays[iarray].bump(nitem);
	
	sums[iarray] += carrays[iarray].new_value - carrays[iarray].old_value;
	nsums[iarray] += narrays[iarray].new_value - narrays[iarray].old_value;

	if (nsites >= winsize) {
	  if (nsums[iarray] > 0) {
	    std::cout << sums[iarray] / nsums[iarray];
	  } else {
	    std::cout << "NA";
	  }
	}
	iarray++;
    }
    if (nsites >= winsize) {
      std::cout << std::endl;
    }
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
