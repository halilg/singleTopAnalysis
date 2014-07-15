
CPP=g++
CPPFLAGS=-I.
LROOT=`root-config --cflags --glibs`

analysis: analysis.h analysis.cc Makefile
	$(CPP) analysis.cc $(CPPFLAGS) $(LROOT) -o $@
