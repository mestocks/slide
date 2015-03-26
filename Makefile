incs = /usr/include/ include/
libs = /usr/lib/

INCLUDE = $(addprefix -I ,$(incs))
LIBS = $(addprefix -L ,$(libs))

.PHONY:	all
all:	slide slmean

%:	%.cpp
	g++ -std=c++0x $(LIBS) $(INCLUDE) -o $@ $^ -lgsl -lgslcblas
