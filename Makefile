all: ppm.out

ppm.out: ppm.c fonctions.c fonctions.o
	gcc -o ppm.out ppm.c fonctions.o	

fonctions.o: fonctions.h fonctions.c
	gcc -o fonctions.o fonctions.c -c
clean:
	rm *.o

mrproper: clean
	rm ppm.out
