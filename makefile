all: filemaster.o dir.o
		gcc dir.o filemaster.o


filemaster.o: filemaster.c filemaster.h
		gcc -c filemaster.c

dir.o: dir.c filemaster.h
		gcc -c dir.c

run:
		./a.out
