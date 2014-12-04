ifndef ROOTSYS                                                                                                                                         
$(error *** Please set up ROOT)                                                                                                                        
endif

CPP=g++
CPPFLAGS=-I. -Wall
LROOT=`root-config --glibs`
CROOT=`root-config --cflags`
LOTHER= #-lboost_system

default: analysis.exe

jsoncpp.o: jsoncpp.cpp json/json-forwards.h json/json.h
	$(CPP) -c jsoncpp.cpp $(CPPFLAGS) -o $@

jsoncpp_cheat.exe: jsoncpp_cheat.cc jsoncpp.o
	$(CPP) jsoncpp_cheat.cc jsoncpp.o $(CPPFLAGS) -o $@

event.o: event.cc event.h Makefile
	$(CPP) -c event.cc $(CPPFLAGS) $(CROOT) -o $@

analysis.o: analysis.h analysis.cc Makefile
	$(CPP) -c analysis.cc $(CPPFLAGS) $(CROOT) -o $@

analysis.exe: event.o analysis.o jsoncpp.o Makefile
	$(CPP) analysis.o event.o jsoncpp.o $(LROOT) -o $@
	
clean:
	$(RM) *.o *.exe
