determinant.out: matrix.o main.o
	gcc -g -Wall -Werror -o determinant.out matrix.o main.o

matrix.o: matrix.c 
	gcc -g -Wall -Werror -c -o matrix.o matrix.c
	
main.o: main.c matrix.h
	gcc -g -Wall -Werror -c -o main.o main.c
	
clean:
	rm -f *.out *.o
