#ifndef __BINTREE_H__
#define __BINTREE_H__

typedef struct {
	int chave;
} info;

typedef struct node {
	info *info;
	struct node *prox, *ant;
} tnode;

typedef struct {
	tnode *top;
	int Size;
}Stack;

typedef struct {
	tnode *first, *last;
	int Size;
}Queue;

typedef struct {
	tnode *first, *last;
	int Size;
}Lista;

info* createinfo(int x);

tnode *createnode(info *x);

Stack *createstack(info *info);

Stack *push(Stack *stk, info *info);

Stack *pop(Stack *stk);

int stacksize(Stack *stk);

tnode *stacktop(Stack *stk);

void printstack(Stack *stk);

Queue *createqueue(info *info);

Queue *Insert(Queue *q, info *info);

Queue *delete(Queue *q);

int queuesize(Queue *q);

tnode *queuefirst(Queue *q);

tnode *queuelast(Queue *q);

void printqueue(Queue *q);

lista *crialistavazia();

lista *crialista(info *info);

lista *inserefim(lista *l, info *info);

lista *insereini(lista *l, info *info);

lista *deletefim(lista *l);

lista *deleteini(lista *l);

tnode *printlistarec(tnode *first);

void printlista(lista *l);

//node do tipo binary tree
typedef struct bt {
	struct bt *esq, *dir;
	info *info;
} bintree;

//1)cria a arvore binaria
bintree *createbt(info *info);

//2) left bt
bintree *leftbt(bintree *bt);

//3)right bt
bintree *rightbt(bintree *bt);

//4) elemento de informacao
info *infobt(bintree *bt);

//5) elemento nulo, ou nao
bool isemptybt(bintree *bt)

//6) verifica se um elemento de informacao esta presente em uma arvore
int isinbt(bintree *bt, info *i);

//7) libera toda a memoria malocada por uma arvore binaria
void destroybt(bintree *root);

//8) calcula a altura de uma arvore binaria
int alturabt(bintree *root);

//9) gera uma lista representando o percurso pre-order da arvore
void montapreorder(bintree *root, lista *l);

lista *listapreorder(bintree *root, lista *l);

//10) gera uma lista representando o percurso in-order da arvore
void montainorder(bintree *root, lista *l);

lista *listainorder(bintree *root, lista *l);

//11) gera uma lista representando o percurso pos-order da arvore
void montaposorder(bintree *root, lista *l);

lista *listaposorder(bintree *root, lista *l);

//16) RETORNA O NODE MAIS A ESQUERDA
bintree *maisesquerda(bintree *root);

//17) RETORNA O NODE MAIS A DIREITA
bintree *maisdireita(bintree *root);

//14) INSERE UM ELEMENTO NA POSICAO MAIS A ESQUERDA
bintree *inseremaisesq(bintree *root, info *info);

//INSERE UM ELEMENTO NA POSICAO MAIS A DIREITA
bintree *inseremaisdir(bintree *root, info *info);

//18) ESPELHA UMA ARVORE
bintree *mirrorbt(bintree *root, bintree *mirror);

//delete
bintree *deletenodebt(bintree *bt, info *info);

//print
void printbt(bintree *root);

#endif // __BINTREE_H__
