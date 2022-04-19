#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DList.h"


lista *crialista() {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	return l;
}

node *crianode(int x) {
	node *novo = (node*) calloc(1, sizeof(node));
	if (!novo)
		return 0;
	novo->valor = x;
	return novo;
}

//(f) impressao
void print(lista *l) {
	printf("\nLista:\t");
	if (!l)
		return;
	node *ptr = l->inicio;
	while (ptr != l->fim) {
		printf("%d ", ptr->valor);
		ptr = ptr->prox;
	}
	if (ptr == l->fim)
		printf("%d ", ptr->valor);

	return;
}

//(a) insere no inicio
lista *insereini(lista *l, int ch) {
	if (!l)
		l = crialista();
	node *novo = crianode(ch);
	node *ptr = l->inicio;
	if (!ptr) {
		novo->prox = novo;
		l->inicio = l->fim = novo;
		return l;
	}
	if (ptr == l->fim) {
		//printf("\nteste1");
		novo->prox = ptr;
		ptr->prox = novo;
		l->inicio = novo;
		return l;
	}
	//printf("\nteste2");
	novo->prox = ptr;
	l->inicio = novo;
	return l;
}

//(b) remove o primeiro
lista *removeini(lista *l) {
	node *ptr = l->inicio;
	if (!l || !ptr)
		return 0;
	if (ptr == l->fim) {
		free(ptr);
		l->inicio = l->fim = 0;
		return l;
	}
	l->inicio = ptr->prox;
	free(ptr);
	return l;
}

//(c) insere fim
lista *inserefim(lista *l, int ch) {
	node *novo = crianode(ch);
	node *ptr = l->fim;
	if (!l)
		l = crialista();
	if (!ptr) {
		novo->prox = novo;
		l->inicio = l->fim = novo;
		return l;
	}
	if (ptr == l->inicio) {
		l->inicio->prox = novo;
		novo->prox = l->inicio;
		l->fim = novo;
		return l;
	}
	ptr->prox = novo;
	l->fim = novo;
	return l;
}

//(d) remove fim
lista *removefim(lista *l) {
	if (!l)
		return 0;
	//printf("\nteste1");
	if (l->inicio == l->fim) {
		//	printf("\nteste2");
		l->inicio = l->fim = 0;
		free(l->inicio);
		return l;
	}
	node *ptr = l->fim;
	node *pptr = l->inicio;
	//printf("\nteste2");
	while (pptr->prox != l->fim)
		pptr = pptr->prox;

	pptr->prox = l->inicio;
	l->fim = pptr;
	free(ptr);
	return l;
}

//(e) remove info
lista *removeinfo(lista *l, int x) {
	if (!l)
		return 0;
	if (l->inicio == l->fim) {
		//printf("\nteste2");
		if (l->inicio->valor == x) {
			free(l->inicio);
			l->inicio = l->fim = 0;
			return l;
		}
		return l;
	}
	//printf("\nteste2.3");
	node *ptr = l->inicio, *pptr;
	while (ptr != l->fim) {
		pptr = ptr;
		//printf("\nteste2.55");
		if (ptr->valor == x) {
			pptr->prox = ptr->prox;
			free(ptr);
			return l;
		}
		ptr = ptr->prox;
	}
	if (ptr == l->fim && ptr->valor == x) {
		pptr->prox = ptr->prox;
		l->fim = pptr;
		free(ptr);
		return l;
	}

	return l;
}
