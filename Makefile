incs = /usr/include/ include/
libs = /usr/lib/

INCLUDE = $(addprefix -I ,$(incs))
LIBS = $(addprefix -L ,$(libs))

.PHONY:	all
all:	slide slmean

%:	%.cpp
	g++ $(LIBS) $(INCLUDE) -o $@ $^ -lgsl -lgslcblas
