#ifndef __BST_H__
#define __BST_H__

typedef struct {
	int chave;
} info;

//árvore de busca binária
typedef struct bt {
	struct bt *esq, *dir;
	info *info;
} bst;

#endif // __BST_H__
