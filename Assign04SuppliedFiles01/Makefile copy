a4s1: sequence.o sequenceTest.o
	g++ sequence.o sequenceTest.o -o a4s1
sequence.o: sequence.cpp sequence.h
	g++ -Wall -ansi -pedantic -c sequence.cpp
sequenceTest.o: sequenceTest.cpp sequence.cpp sequence.h
	g++ -Wall -ansi -pedantic -c sequenceTest.cpp

test:
	./a4s1 auto < a4test.in > a4test.out
clean:
	@rm -rf sequence.o sequenceTest.o
cleanall:
	@rm -rf sequence.o sequenceTest.o a4s1

