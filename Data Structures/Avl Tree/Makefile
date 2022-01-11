
### Makefile ###

# Alvo all -> onde realizar
all: exec

exec: avl.o main.o
	gcc -o exec avl.o main.o

main.o: main.c avl.h
	gcc -c main.c

avl.o:	avl.c avl.h
	gcc -c avl.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios
clean:
	rm -rf *.o
