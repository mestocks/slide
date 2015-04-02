#include <map>
#include <string>
#include <vector>

std::map<std::string, std::string> argasso(int argc,
					   char *argv[],
					   std::map<std::string, int> argtype,
					   std::map<std::string, std::string> argopts) {
  // Returns an associative array of <args, opts> from the arguments string

  // Requires an associative array of argument types, where 1 means that an
  // value is required and 0 means that no value is required. Could be defined
  // like this:

  // std::map<std::string, int> argtype {
  //  {"-k", 1}, {"-n", 0} };

  // And also an associative array that defines the viable arguments and their
  // default values. E.g.:

  // std::map<std::string, std::string> argopts {
  //  {"-k", "1"}, {"-n", "0"}
  // };

  // For the command line:
  
  // -k 4,5 -n

  // Using:
  
  // argopts = argasso(argc, argv, argtype, argopt);
  // std::cout << argopts["-k"] << " " << argopts["-n"] << std::endl;
  //
  // Would give:

  // 4,5 1

  
    int argindex = 0;
    std::string argkey;
    std::string argvalue;
    
    for (int i = 1; i < argc; i++) {
      if (argindex == 0) {
	argindex = argtype[argv[i]];
	argkey = argv[i];
	if (argindex == 0) {
	  argopts[argkey] = "1";
	}
      } else {
	argindex--;
	argopts[argkey] = argv[i];
      }
    }
    return argopts;
}

std::vector<int> parse_cols(std::string meancols) {
  // Parse a string indicating a range of values into
  // a vector. The ordering given by the string is
  // preserved.

  // Examples:
  // "2"         < 2 >
  // "2,3"       < 2, 3 >
  // "1-3"       < 1, 2, 3 >
  // "3,4-7"     < 3, 4, 5, 6, 7 >
  // "7,6,3-9"   < 7, 6, 3, 4, 5, 6, 7, 8, 9>
  
  std::vector<int> columns;
  
  std::string tmpstr = "";
  for (int i =0; i < meancols.size(); i++) {
    
    if (meancols[i] != ',') {
      tmpstr += meancols[i];
    } else {

      if (tmpstr.find('-') == std::string::npos) {
    	columns.push_back(stoi(tmpstr));
    	tmpstr = "";
      } else {
	
	int dash = 0;
	int start;
	int end;
	std::string tmpdash = "";
	for (int j = 0; j < tmpstr.size(); j++) {

	  if (tmpstr[j] == '-') {
	    dash = 1;
	    start = stoi(tmpdash);
	    tmpdash = "";
	  } else {
	    if (dash == 0) { tmpdash += tmpstr[j]; }
	    else { tmpdash += tmpstr[j]; }
	  }
	}
	end = stoi(tmpdash);
	while (start <= end) { columns.push_back(start); start++; }
	
      }
      tmpstr = "";
    }
  }

  if (tmpstr.find('-') == std::string::npos) {
    columns.push_back(stoi(tmpstr));
    tmpstr = "";
  } else {
    
    int dash = 0;
    int start;
    int end;
    std::string tmpdash = "";
    for (int j = 0; j < tmpstr.size(); j++) {
      
      if (tmpstr[j] == '-') {
	dash = 1;
	start = stoi(tmpdash);
	tmpdash = "";
      } else {
	if (dash == 0) { tmpdash += tmpstr[j]; }
	else { tmpdash += tmpstr[j]; }
      }
    }
    end = stoi(tmpdash);
    while (start <= end) { columns.push_back(start); start++; }
  }
  
  return columns;
}
