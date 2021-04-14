#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "BST.c.c"

int main() {

//informacoes
	info *d1 = createinfo(101);
	info *d2 = createinfo(20);
	info *d3 = createinfo(31);
	info *d4 = createinfo(44);
	info *d5 = createinfo(55);

//nos
	bst *tree = createbst(d1);
	tree = insertbst(tree, d2);
	tree = insertbst(tree, d3);
	tree = insertbst(tree, d4);
	tree = insertbst(tree, d5);
	tree = deletebst(tree, d3);

	printf("\n************************\narvore binaria de busca: ");
	printbst(tree);

	printf("\nmaior: %d", maiorbst(tree)->info->chave);
	printf("\nmenor: %d", menorbst(tree)->info->chave);

	return 0;
}
