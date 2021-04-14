#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "BST.h.h"

//cria info
info* createinfo(int x) {
	info *data = (info*) calloc(1, sizeof(info));
	if (!data)
		return 0;
	data->chave = x;
	return data;
}

//cria bst
bst *createbst(info *info) {
	if (!info)
		return 0;
	bst *novo = (bst*) calloc(1, sizeof(bst));
	if (!novo)
		return 0;
	novo->info = createinfo(info->chave);
	return novo;
}

//print bst
void printbst(bst *bst) {
	if (!bst)
		return;
	printbst(bst->esq);
	printf("\t%d", bst->info->chave);
	printbst(bst->dir);
	return;
}

//busca bst
bst *buscabst(bst *root, info *info) {
	if (root->info->chave == info->chave) {
		return root;
	}
	if (root->info->chave > info->chave)
		return buscabst(root->esq, info);
	else
		return buscabst(root->dir, info);
}

//insert na bst
bst *insertbst(bst *root, info *info) {
	bst *novo = createbst(info);
	if (!root) {
		root = novo;
		return novo;
	}
	if (root->info->chave > info->chave)
		root->esq = insertbst(root->esq, info);
	if (root->info->chave < info->chave)
		root->dir = insertbst(root->dir, info);
	return root;
}

//retorna o maior elemento dentro de uma arvore
bst *maiorbst(bst *root) {
	if (!root)
		return 0;
	bst *temp = root;
	while (temp->dir)
		temp = temp->dir;
	return temp;
}

//retorna o menor elemento dentro de uma arvore
bst *menorbst(bst *root) {
	if (!root)
		return 0;
	bst *temp = root;
	while (temp->esq)
		temp = temp->esq;
	return temp;
}

//esta na bst
int isinbt(bst *root, info *i) {
	if (root->info == i)
		return 1;
	else {
		if (isinbt(root->esq, i) || isinbt(root->dir, i))
			return 1;
		else
			return 0;
	}
}

//deleta um node da lista
bst *deletebst(bst *bst, info *info) {
	if (!bst)
		return bst;
	if (info->chave < bst->info->chave)
		bst->esq = deletebst(bst->esq, info);
	else if (info->chave > bst->info->chave)
		bst->dir = deletebst(bst->dir, info);
	else {
		struct bt *temp;
		if (!bst->esq) {
			temp = bst->dir;
			free(bst->info);
			free(bst);
			return temp;
		} else if (!bst->dir) {
			temp = bst->esq;
			free(bst->info);
			free(bst);
			return temp;
		}
		temp = menorbst(bst->dir);
		bst->info = temp->info;
		bst->dir = deletebst(bst->dir, temp->info);
	}
	return bst;

}
