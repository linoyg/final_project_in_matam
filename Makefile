CC =/usr/local/bin/g++
OBJS_GCALC= Commands.o Expression.o Graph.o RunShell.o Shell.o Tokenize.o PyGraph.o
EXEC_GCALC = gcalc
DEBUG_FLAG = -g # empty or -g for debugging
COMP_FLAG = -std=c++11 -fPIC -Wall -Werror -pedantic-errors -DNDEBUG 
OBJS= Commands.o Expression.o Graph.o RunShell.o Shell.o Tokenize.o PyGraph.o
# Test GCALC
$(EXEC_GCALC) : $(OBJS_GCALC)
	$(CC) $(DEBUG_FLAG) $(OBJS_GCALC) -o $@

Commands.o: Commands.cpp Commands.h Tokenize.h Graph.h Expression.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Expression.o: Expression.cpp Expression.h Graph.h Tokenize.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Graph.o: Graph.cpp Graph.h Tokenize.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

RunShell.o: RunShell.cpp Graph.h Tokenize.h Commands.h Expression.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Shell.o: Shell.cpp Graph.h RunShell.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Tokenize.o: Tokenize.cpp Tokenize.h Graph.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
PyGraph.o: PyGraph.cpp PyGraph.h Graph.h RunShell.h Tokenize.h Commands.h Expression.h Shell.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
		
libgraph.a: $(OBJS)
	ar -rs $@ $^	
tar:
	zip gcalc.zip Makefile graph.i design.pdf exp_1.txt in_1.txt Commands.cpp Commands.h Tokenize.h Graph.h Expression.h Expression.cpp RunShell.cpp Shell.cpp Tokenize.cpp PyGraph.cpp Graph.cpp Shell.h RunShell.h PyGraph.h
	
# Clean MtmParkingLot ".o" files
clean : 
	rm -f libgraph.a $(OBJS_GCALC) $(EXEC_GCALCT)