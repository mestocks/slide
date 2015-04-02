incs = /usr/include/ include/ /usr/local/include/htslib/ /usr/local/bin/
libs = /usr/lib/ /usr/local/lib/ /usr/local/pkgconfig/  /usr/local/bin/

INCLUDE = $(addprefix -I ,$(incs))
LIBS = $(addprefix -L ,$(libs))

.PHONY:	all
all:	slide slmean slmean2 #testhtslib

%:	%.cpp
	g++ -std=c++0x $(LIBS) $(INCLUDE) -o $@ $^ -lgsl -lgslcblas

testhtslib:	testhtslib.cpp
	g++ -o $@ $^ -l hts -L /usr/local/lib/
