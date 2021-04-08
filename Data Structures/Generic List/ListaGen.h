#ifndef __LISTAGEN_H__
#define __LISTAGEN_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct listagen {
    void *info;
    struct listagen *prox;
}ListaGen;

ListaGen *cria_listagen(void *v);

ListaGen *insere_listagen(ListaGen *L, void *v);

void percorre_listagen(ListaGen *L, void (*cb)(void *));

#endif
