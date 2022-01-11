### Makefile ###

# Alvo all -> onde realizar
all: exec

exec: treeRN.o mainTreeRN.o
	gcc -o exec treeRN.o mainTreeRN.o

mainTreeRN.o: mainTreeRN.c treeRN.h
	gcc -c mainTreeRN.c

treeRN.o:	treeRN.c treeRN.h
	gcc -c treeRN.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios
clean:
	rm -rf *.o

