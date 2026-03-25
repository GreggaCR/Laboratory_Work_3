all: matrix_lib2

matrix_lib2: main2.o matrix2.o fraction2.o
		g++ -Wall -std=c++11 main2.o matrix2.o fraction2.o -o matrix_lib2  -lgmpxx -lgmp

main2.o: main2.cxx
		g++ -Wall -std=c++11 -c main2.cxx

matrix2.o: matrix2.cxx
	g++ -Wall -std=c++11 -c matrix2.cxx

fraction2.o: fraction2.cxx
	g++ -Wall -std=c++11 -c fraction2.cxx

clean:
	rm -rf *.o matrix_lib2
