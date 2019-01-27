ex5: ex5.o Vector.o
	gcc -Wall -g -std=c11 -o ex5 ex5.o Vector.o
ex5.o: ex5.c Vector.h
	gcc -Wall -g -std=c11 -c ex5.c
Vector.o: Vector.c Vector.h
	gcc -Wall -g -std=c11 -c Vector.c
clean:
	rm -rf ex5 *.o *~ ex5.dSYM
