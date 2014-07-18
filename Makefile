ifndef ROOTSYS                                                                                                                                         
$(error *** Please set up ROOT)                                                                                                                        
endif

CPP=g++
CPPFLAGS=-I.
LROOT=`root-config --cflags --glibs`
LOTHER= #-lboost_system

analysis.exe: event.o analysis.o Makefile
	$(CPP) analysis.o event.o $(LROOT) $(LOTHER) -o $@

event.o: event.cc event.h
	$(CPP) -c event.cc $(CPPFLAGS) $(LROOT) -o $@

analysis.o: analysis.h analysis.cc Makefile
	$(CPP) -c analysis.cc $(CPPFLAGS) $(LROOT) $(LOTHER) -o $@
	
clean:
	rm *.o analysis
