### Makefile ###

# Alvo all -> onde realizar
all: exec

exec: huffman.o mainHuffman.o
	gcc -o exec huffman.o mainHuffman.o

mainHuffman.o: mainHuffman.c huffman.h
	gcc -c mainHuffman.c

huffman.o:	huffman.c huffman.h
	gcc -c huffman.c

# Alvo clean -> Apagar objetos (*.o) e outros arquivos temporarios
clean:
	rm -rf *.o

