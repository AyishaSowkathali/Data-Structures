ao1: btNode.o AssignOpt01.o
	g++ btNode.o AssignOpt01.o -o ao1
btNode.o: btNode.cpp btNode.h
	g++ -Wall -ansi -pedantic -c btNode.cpp
AssignOpt01.o: AssignOpt01.cpp btNode.h
	g++ -Wall -ansi -pedantic -c AssignOpt01.cpp

go:
	./ao1
gogo:
	./ao1 > ao1.out
nt:
	@rm -rf *.h *.cpp *o *.out ao1
clean:
	@rm -rf btNode.o AssignOpt01.o
cleanall:
	@rm -rf btNode.o AssignOpt01.o ao1
