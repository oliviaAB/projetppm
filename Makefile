all: ppm

ppm: ppm.cpp fonctions.cpp fonctions.o
	g++ -Wall -o ppm ppm.cpp fonctions.o	

fonctions.o: fonctions.h fonctions.cpp
	g++ -Wall -o fonctions.o fonctions.cpp -c
clean:
	rm *.o

mrproper: clean
	rm ppm.out
