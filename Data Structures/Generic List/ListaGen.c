#include "ListaGen.h"

ListaGen *cria_listagen(void *v){
    ListaGen *novo = (ListaGen *)calloc(1, sizeof(ListaGen));
    if(novo == NULL){
        printf("Erro: nao foi possivel alocar estrutura. \n");
        exit(1);
    }
    novo->info = v;
    return novo;
}

ListaGen *insere_listagen(ListaGen *L, void *v){
    ListaGen *novo = cria_listagen(v);
    novo->prox = L;
    return novo;
}

void percorre_listagen(ListaGen *L, void (*cb)(void *)){
    ListaGen *aux = L;
    while(aux != NULL){
        cb(aux->info);
        aux = aux->prox;
    }
}
