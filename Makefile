all: ppm

ppm: ppm.cpp Image.cpp Image.o
	g++ -Wall -o ppm ppm.cpp Image.o	

fonctions.o: Image.h Image.cpp
	g++ -Wall -o Image.o Image.cpp -c
clean:
	rm *.o

mrproper: clean
	rm ppm.out
