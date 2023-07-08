all: DNAcrack

DNAcrack: DNAcrack.c analyze.o cut.o glue.o listas.o recombine.o 
	gcc DNAcrack.c analyze.o cut.o glue.o listas.o recombine.o -o DNAcrack

analyze.o: analyze.h analyze.c
	gcc -c analyze.c -o analyze.o

cut.o: cut.h cut.c
	gcc -c cut.c -o cut.o

glue.o: glue.h glue.c
	gcc -c glue.c -o glue.o

listas.o : listas.h listas.c
	gcc -c listas.c -o listas.o

recombine.o: recombine.h recombine.c
	gcc -c recombine.c -o recombine.o

clean :
	rm -f *.o DNAcrack