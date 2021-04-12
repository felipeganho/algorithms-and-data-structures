#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binTree.cpp"

int main(){
//------------------------------------------INFORMACOES----------------------------------------------
	info *d1 = createinfo(1);
	info *d2 = createinfo(2);
	info *d3 = createinfo(3);
	info *d4 = createinfo(4);
	info *d5 = createinfo(5);

//-------------------------------------------NODES---------------------------------------------------
	tnode *p1 = createnode(d1);
	tnode *p2 = createnode(d2);
	tnode *p3 = createnode(d3);
	tnode *p4 = createnode(d4);
	tnode *p5 = createnode(d5);

//-------------------------------------------ARVORE---------------------------------------------------

	bintree *t1 = createbt(d1);
	t1 = inseremaisdir(t1, d2);
	t1 = inseremaisesq(t1, d3);
	t1 = inseremaisesq(t1, d4);
	t1 = inseremaisdir(t1, d5);
	t1 = deletenodebt(t1, d1);

	printf("\narvore: ");
	printbt(t1);
	printf("\n\npassou");

	lista *l = crialistavazia();
	l = listainorder(t1, l);

	printf("\n%d",l->size);
	printf("\n\npassou");

	return 0;
}
