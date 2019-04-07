all: Projet_C clean

pFile.o: pFile.c pFile.h
	gcc -c pFile.c

graph.o: graph.c graph.h pFile.h
	gcc -c -lm graph.c

Projet_C.o: Projet_C.c graph.h
	gcc -c Projet_C.c

Projet_C: Projet_C.o pFile.o graph.o
	gcc Projet_C.o pFile.o graph.o -lm -o Projet_C
clean: 
	rm -rf *.o

mrproper: clean
	rm -rf Projet_C
