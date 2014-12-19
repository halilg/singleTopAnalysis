ifndef ROOTSYS                                                                                                                                         
$(error *** Please set up ROOT)                                                                                                                        
endif

CPP=g++
CPPFLAGS=-I. -Wall
LROOT=`root-config --glibs`
CROOT=`root-config --cflags`
LOTHER= #-lboost_system
ODIR=temp

default: analysis.exe

all: analysis.exe jsoncpp_cheat.exe analyze_yields.exe readcfg.exe make_plots_stack.exe

$(ODIR)/jsoncpp.o: jsoncpp.cpp json/json-forwards.h json/json.h
	$(CPP) -c jsoncpp.cpp $(CPPFLAGS) -o $@

jsoncpp_cheat.exe: jsoncpp_cheat.cc $(ODIR)/jsoncpp.o
	$(CPP) jsoncpp_cheat.cc $(ODIR)/jsoncpp.o $(CPPFLAGS) -o $@

$(ODIR)/json2tchain.o: json2tchain.cc json2tchain.h
	$(CPP) -c json2tchain.cc $(CPPFLAGS) $(CROOT) -o $@

$(ODIR)/event.o: event.cc event.h Makefile
	$(CPP) -c event.cc $(CPPFLAGS) $(CROOT) -o $@

$(ODIR)/analysis.o: analysis.h analysis.cc Makefile
	$(CPP) -c analysis.cc $(CPPFLAGS) $(CROOT) -o $@

analysis.exe: $(ODIR)/event.o $(ODIR)/analysis.o $(ODIR)/jsoncpp.o $(ODIR)/json2tchain.o git_ref.h Makefile
	echo "#define GIT_REF \"`git show-ref refs/heads/master | cut -d " " -f 1 | cut -c 31-40`\"" > git_ref.h
	$(CPP) $(ODIR)/analysis.o $(ODIR)/event.o $(ODIR)/jsoncpp.o $(ODIR)/json2tchain.o $(LROOT) -o $@

$(ODIR)/analyze_yields.o: analyze_yields.cc
	$(CPP) -c analyze_yields.cc $(CPPFLAGS) -o $@

$(ODIR)/cfgreader.o: cfgreader.cc cfgreader.h
	$(CPP) -c cfgreader.cc $(CPPFLAGS) -o $@

readcfg.exe: readcfg.cc $(ODIR)/cfgreader.o $(ODIR)/jsoncpp.o
	$(CPP) $(CPPFLAGS) readcfg.cc $(ODIR)/cfgreader.o $(ODIR)/jsoncpp.o -o $@
	
analyze_yields.exe: $(ODIR)/analyze_yields.o $(ODIR)/jsoncpp.o $(ODIR)/cfgreader.o Makefile
	$(CPP) $(ODIR)/analyze_yields.o $(ODIR)/jsoncpp.o $(ODIR)/cfgreader.o -o $@

$(ODIR)/make_plots_stack.o: make_plots_stack.cc
	$(CPP) -c make_plots_stack.cc $(CPPFLAGS) $(CROOT) -o $@

make_plots_stack.exe: $(ODIR)/make_plots_stack.o  $(ODIR)/jsoncpp.o $(ODIR)/cfgreader.o
	$(CPP) $(ODIR)/make_plots_stack.o $(ODIR)/jsoncpp.o $(ODIR)/cfgreader.o $(LROOT) -o $@

	
clean:
	$(RM) $(ODIR)/*.o *.exe
