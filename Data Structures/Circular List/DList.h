#ifndef __DLIST_H__
#define __DLIST_H__

typedef struct tnode {
	int valor;
	struct tnode *prox;
} node;

typedef struct {
	struct tnode *inicio, *fim;
} lista;

lista *crialista();

node *crianode(int x);

//impressao
void print(lista *l);

// insere no inicio
lista *insereini(lista *l, int ch);

//remove o primeiro
lista *removeini(lista *l);

// insere fim
lista *inserefim(lista *l, int ch);

// remove fim
lista *removefim(lista *l);

//remove info
lista *removeinfo(lista *l, int x);


#endif // __DLIST_H__

