#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binTree.h"

info* createinfo(int x) {
	info *data = (info*) calloc(1, sizeof(info));
	if (!data)
		return 0;
	data->chave = x;
	return data;
}

tnode *createnode(info *x) {
	tnode *novo = (tnode*) calloc(1, sizeof(tnode));
	if (!novo || !x) {
		return 0;
	}
	novo->info = x; //calloc ja aponta os ponteiros para null, logo nao precisa se reapontar prox e ant;
	return novo;
}

//****************************************************************************
//--------------------------- FUNCOES STACK ----------------------------------
//****************************************************************************
stack *createstack(info *info) {
	tnode *elem = createnode(info);
	stack *stk = (stack*) calloc(1, sizeof(stack));
	if (stk && elem) {
		stk->size = 1;
		stk->top = elem;
		return stk;
	} else
		return 0;
}

stack *push(stack *stk, info *info) {
	tnode *elem = createnode(info);
	if ((stk && stk->size > 0) && elem) {
		tnode *ptr = stk->top;
		ptr->prox = elem;
		elem->ant = ptr;
		stk->top = elem;
		stk->size++;
		return stk;
	} else
		return 0;
}

stack *pop(stack *stk) {
	if (!stk || stk->size <= 0)
		return 0;
	tnode *ptr = stk->top;
	ptr->ant->prox = 0; //2 ou mais elementos
	stk->top = ptr->ant;
	stk->size--;
	free(ptr->info);
	free(ptr);
	return stk;
}

int stacksize(stack *stk) {
	return stk->size;
}

tnode *stacktop(stack *stk) {
	return stk->top;
}

void printstack(stack *stk) {
	printf("pilha:");
	if (!stk || stk->size <= 0)
		return;
	if (stk->size == 1) {
		printf("\n[%d]", stk->top->info->chave);
		return;
	}
	tnode *ptr = stk->top;
	while (ptr) {
		printf("\n[%d]", ptr->info->chave);
		ptr = ptr->ant;
	}
	return;
}

//****************************************************************************
//--------------------------- FUNCOES QUEUE ----------------------------------
//****************************************************************************
queue *createqueue(info *info) {
	tnode *elem = createnode(info);
	queue *q = (queue*) calloc(1, sizeof(queue));
	if (q && elem) {
		q->size = 1;
		q->first = elem;
		q->last = elem;
		return q;
	} else
		return 0;
}

queue *insert(queue *q, info *info) {
	tnode *elem = createnode(info);
	if ((q && q->size >= 1) && elem) {
		tnode *ptr = q->last;
		ptr->prox = elem;
		elem->ant = ptr;
		q->last = elem;
		q->size++;
		return q;
	} else
		return 0;
}

queue *delete(queue *q) {
	if (!q || q->size <= 0)
		return NULL;
	tnode *ptr = q->first;
	q->first = ptr->prox;
	free(ptr->info);
	free(ptr);
	return q;
}

int queuesize(queue *q) {
	return q->size;
}

tnode *queuefirst(queue *q) {
	return q->first;
}

tnode *queuelast(queue *q) {
	return q->last;
}

void printqueue(queue *q) {
	printf("\n\nfila:\t");
	if (!(q->size || q))
		return;
	tnode *ptr = q->first;
	while (ptr) {
		printf("[%d]\t", ptr->info->chave);
		ptr = ptr->prox;
	}
	return;
}

//****************************************************************************
//--------------------------- FUNCOES LISTA ----------------------------------
//****************************************************************************
lista *crialistavazia() {
	lista *l = (lista*) calloc(1, sizeof(lista));
	if (!l)
		return 0;
	/**
	 * calloc ja zera todos os apontamentos
	 */
	return l;
}

lista *crialista(info *info) {
	lista *l = (lista*) calloc(1, sizeof(lista));
	tnode *elem = createnode(info);
	if (l && elem) {
		l->first = elem;
		l->last = elem;
		l->size = 1;
		return l;
	} else
		return 0;
}

lista *inserefim(lista *l, info *info) {
	if (!l || l->size <= 0) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l->size == 1 && elem) {
		l->last->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	}
	if (l && elem) {
		tnode *ptr = l->last;
		ptr->prox = elem;
		l->last = elem;
		l->size++;
		return l;
	} else
		return 0;
}

lista *insereini(lista *l, info *info) {
	if (!l || l->size <= 0) {
		l = crialista(info);
		return l;
	}
	tnode *elem = createnode(info);
	if (l->size == 1 && elem) {
		elem->prox = l->first;
		l->first = elem;
		l->last = elem;
		l->size++;
		return l;
	}
	if (l && elem) {
		tnode *ptr = l->first;
		elem->prox = ptr;
		l->first = elem;
		l->size++;
		return l;
	} else
		return 0;
}

lista *deletefim(lista *l) {
	if (!l || l->size <= 0)
		return l;
	if (l->size == 1) {
		tnode *ptr = l->first = l->last;
		l->first = l->last = 0;
		free(ptr->info);
		free(ptr);
		l->size--;
		return l;
	}
	tnode *ptr = l->first;
	tnode *ptr2 = ptr->prox;
	while (ptr2->prox) {
		ptr = ptr2;
		ptr2 = ptr2->prox;
	}
	free(ptr2->info);
	free(ptr2);
	ptr->prox = 0;
	l->last = ptr;
	l->size--;
	return l;
}

lista *deleteini(lista *l) {
	if (!l || l->size <= 0)
		return l;
	if (l->size == 1) {
		tnode *ptr = l->first;
		l->last = 0;
		l->first = 0;
		l->size--;
		free(ptr->info);
		free(ptr);
		return l;
	}
	tnode *ptr = l->first;
	l->first = ptr->prox;
	l->size--;
	free(ptr->info);
	free(ptr);
	return l;
}

tnode *printlistarec(tnode *first) {
	if (first) {
		printf("\t[%d]", first->info->chave);
		return printlistarec(first->prox);
	} else
		return 0;
}

void printlista(lista *l) {
	if (!l || l->size <= 0)
		return;
	tnode *ptr = l->first;
	while (ptr) {
		printf("[%d]\t", ptr->info->chave);
		ptr = ptr->prox;
	}
}

//*****************************************************************************************
//----------------------------------- ARVORE BINARIA --------------------------------------
//*****************************************************************************************

//node do tipo binary tree
typedef struct bt {
	struct bt *esq, *dir;
	info *info;
} bintree;

//1)cria a arvore binaria
bintree *createbt(info *info) {
	bintree *root = (bintree*) calloc(1, sizeof(bintree)); //quando se gera uma arvore, se cria a raiz
	if (!root)
		return 0;
	root->info = info;
	return root;
}

//2) left bt
bintree *leftbt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->esq;
}

//3)right bt
bintree *rightbt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->dir;
}

//4) elemento de informacao
info *infobt(bintree *bt) {
	if (!bt)
		return 0;
	return bt->info;
}

//5) elemento nulo, ou nao
bool isemptybt(bintree *bt) {
	if (!bt)
		return true;
	else
		return false;
}

//******************************************************************
//6) verifica se um elemento de informacao esta presente em uma arvore
int isinbt(bintree *bt, info *i) {
	if (bt->info == i)
		return 1;
	else {
		if (isinbt(bt->esq, i))
			return 1;
		if (isinbt(bt->dir, i))
			return 1;
		else
			return 0;
	}
}

//7) libera toda a memoria malocada por uma arvore binaria
void destroybt(bintree *root) {
	if (!root)
		return;
	else {
		destroybt(root->esq);
		destroybt(root->dir);
		free(root->info);
		free(root);
		return;
	}
}

//8) calcula a altura de uma arvore binaria
int alturabt(bintree *root) {
	if (!root)
		return 0;
	else {
		int e, d;
		e = 1 + alturabt(root->esq);
		d = 1 + alturabt(root->dir);
		if (e > d)
			return e;
		else
			return d;
	}
}

//9) gera uma lista representando o percurso pre-order da arvore
void montapreorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return;

	l = inserefim(l, temp);
	montapreorder(root->esq, l);
	montapreorder(root->dir, l);
}

lista *listapreorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return 0;

	l = inserefim(l, temp);
	montapreorder(root->esq, l);
	montapreorder(root->dir, l);
	return l;
}

//10) gera uma lista representando o percurso in-order da arvore
void montainorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return;

	montainorder(root->esq, l);
	l = inserefim(l, temp);
	montainorder(root->dir, l);
}

lista *listainorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return 0;

	montainorder(root->esq, l);
	l = inserefim(l, temp);
	montainorder(root->dir, l);
	return l;
}


//11) gera uma lista representando o percurso pos-order da arvore
void montaposorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return;

	montaposorder(root->esq, l);
	montaposorder(root->dir, l);
	l = inserefim(l, temp);
}

lista *listaposorder(bintree *root, lista *l) {
	info *temp = createinfo(root->info->chave);
	if (isemptybt(root) || !l || !temp)
		return 0;

	montaposorder(root->esq, l);
	montaposorder(root->dir, l);
	l = inserefim(l, temp);
	return l;
}

//12) gera uma lista representando o percurso por niveis da arvore

//13) RECONSTRUIR UMA BT, DADOS SEUS PERCURSOS INORDER E POSORDER

//16) RETORNA O NODE MAIS A ESQUERDA
bintree *maisesquerda(bintree *root) {
	if (!root)
		return 0;
	bintree *temp = root;
	while (leftbt(temp))
		temp = temp->esq;
	return temp;
}

//17) RETORNA O NODE MAIS A DIREITA
bintree *maisdireita(bintree *root) {
	if (!root)
		return 0;
	bintree *temp = root;
	while (rightbt(temp))
		temp = temp->dir;
	return temp;
}

//14) INSERE UM ELEMENTO NA POSICAO MAIS A ESQUERDA
bintree *inseremaisesq(bintree *root, info *info) {
	bintree *novo = createbt(info);
	if (!root) {
		root = novo;
		return root;
	}
	bintree *temp = maisesquerda(root);
	temp->esq = novo;
	return root;
}

//15) INSERE UM ELEMENTO NA POSICAO MAIS A DIREITA
bintree *inseremaisdir(bintree *root, info *info) {
	bintree *novo = createbt(info);
	if (!root) {
		root = novo;
		return root;
	}
	bintree *temp = maisdireita(root);
	temp->dir = novo;
	return root;
}

//18) ESPELHA UMA ARVORE
bintree *mirrorbt(bintree *root, bintree *mirror) {
	if (!root)
		return 0;
	mirror = root;
	mirror->dir = inseremaisdir(root->dir, root->esq->info);
	mirror->esq = inseremaisesq(root->esq, root->dir->info);
	return mirror;
}

//19) DELETE BT. usei o mesmo raciocinio de aula
bintree *deletenodebt(bintree *bt, info *info) {
	if (!bt)
		return 0;
	if (isinbt(bt, info)) {
		if (bt->info == info) {
			bintree *temp1 = leftbt(bt), *temp2 = rightbt(bt);
			if (isemptybt(temp1))
				return temp2;
			else {
				maisdireita(temp1)->dir = temp2;
				return temp1;
			}
		} else {
			if (isinbt(leftbt(bt), info))
				bt->esq = deletenodebt(bt->esq, info);
			else
				bt->dir = deletenodebt(bt->dir, info);
		}
		return bt;
	} else
		return 0;
}

//20) PRINT BT
void printbt(bintree *root) {
	if (!root)
		return;
	printbt(root->esq);
	printf("%d\t", root->info->chave);
	printbt(root->dir);
	return;
}

