all: matrix_lib

matrix_lib: main.o matrix.o fraction.o
		g++ -Wall -std=c++11 main.o matrix.o fraction.o -o matrix_lib -lgmpxx -lgmp

main.o: main.cxx
		g++ -Wall -std=c++11 -c main.cxx

matrix.o: matrix.cxx
	g++ -Wall -std=c++11 -c matrix.cxx

fraction.o: fraction.cxx
	g++ -Wall -std=c++11 -c fraction.cxx

clean:
	rm -rf *.o matrix_lib
