#include <stdio.h>
#include <stdlib.h>
#include "SkipList.h"

/* aloca memória para a cabeça e os nós, e retorna a estrutura criada*/
SkipList *createAll(){
    SkipList *skpLst;
    if(!(skpLst=(SkipList *)malloc(sizeof(SkipList)))) return NULL;
    if(!(skpLst->first=(Node *)malloc(sizeof(Node)))) return NULL;
    for(int i=0;i<MAXNIVEIS;i++){
        skpLst->first->next[i]=NULL;
    }
    skpLst->first->value=0;
    return skpLst;
}

/* cria cabeça da estrutura */
SkipList *createHead(){
    SkipList *skpLst;
    skpLst=(SkipList *)malloc(sizeof(SkipList));
    return skpLst;
}

/* cria os nós da estrutura */
void createList(SkipList *skpLst){
    skpLst->first=(Node *)malloc(sizeof(Node));
    for(int i=0;i<MAXNIVEIS;i++){
        skpLst->first->next[i]=NULL;
    }
    skpLst->first->value=0;
}

/* cria a estrutura apontador */
Apontador *createApont(){
    Apontador *ListaH=(Apontador *)malloc(sizeof(Apontador));
    for(int i=0;i<MAXNIVEIS;i++){
        ListaH->niveis[i]=NULL;
    }
    return ListaH;
}

/* cria nó */
Node *createNode(int value){
    Node *aux=(Node *)malloc(sizeof(Node));
    for(int i=0;i<MAXNIVEIS-1;i++){
        aux->next[i]=NULL;
    }
    aux->value=value;
    return aux;
}

/* verifica se a lista e vazia, caso seja retorna 1, senão retorna 0 */
int isEmptyList(SkipList *skpLst){
    for(int i=0;i<MAXNIVEIS;i++){
        if(!skpLst->first->next[i])
            i++;
        else
            return 0;
    }
    return 1;
}

/* busca o valor passado como parâmetro pela lista, caso encontre retorna 1, senão retorna 0 */
int searchList(int value,SkipList *skpLst,Apontador *ListaH,int imprimir){
    Node *aux=skpLst->first;
    int i=0;
    for(i=MAXNIVEIS-1;i>=0;i--){
        while((aux->next[i] != NULL) && (aux->next[i]->value < value)){
            aux=aux->next[i];
        }
        ListaH->niveis[i]=aux;
    }
    i++;
    if(aux->next[i] && aux->next[i]->value == value){
        if(imprimir==1){
            Apontador *auxPrint=ListaH;
            for(int i=MAXNIVEIS-1;i>=0;i--){
                if(auxPrint->niveis[i]==skpLst->first && !auxPrint->niveis[i]->next[i]) continue;
                printf("%d %d\n",auxPrint->niveis[i]->value,i);
                gravaSaidaPrint(auxPrint->niveis[i]->value,i);
            }
            printf("%d %d\n",auxPrint->niveis[0]->next[0]->value,0);
            gravaSaidaPrint(auxPrint->niveis[0]->next[0]->value,0);
        }
        gravaSaidaStr("true\n");
        printf("true\n");
        return 1;
    }
    gravaSaidaStr("false\n");
    printf("false\n");
    return 0;
}

/* insere nó na estrutura */
int Insere(int value,int h,SkipList *skpLst){
    Apontador *ListaH=createApont();

    if(searchList(value,skpLst,ListaH,0)==1){
        return 0;
    }

    Node *aux=createNode(value);

    for(int i=h;i>=0;i--){
        aux->next[i]=ListaH->niveis[i]->next[i];
        ListaH->niveis[i]->next[i]=aux;
    }
    return 1;
}

/* remove nó da estrutura */
int removeList(int value,SkipList *skpLst){
    Node *aux;
    Apontador *ListaH=createApont();
    if(searchList(value,skpLst,ListaH,0)==0) return 0;
    aux=ListaH->niveis[0]->next[0];
    for(int i=MAXNIVEIS-1;i>=0;i--){
        if(ListaH->niveis[i]->next[i]==NULL)
            continue;
        ListaH->niveis[i]->next[i]=ListaH->niveis[i]->next[i]->next[i];
    }
    free(aux);
    return 1;
}

/* lista todos os elementos pertencentes a uma hierarquia */
void printListH(SkipList *skpLst, int h){
    if(isEmptyList(skpLst)){
      printf("false\n");
      gravaSaidaStr("false\n");
    }
    Node *aux=skpLst->first;
    while(aux->next[h]){
        printf("%d %d\n",aux->next[h]->value, h);
        gravaSaidaPrint(aux->next[h]->value,h);
        aux=aux->next[h];
    }
    gravaSaidaStr("true\n");
    printf("true\n");
}

/* lista todos os elementos pertencentes a estrutura */
void printList(SkipList *skpLst){
    Node *aux;
    for(int i=MAXNIVEIS-1;i>=0;i--){
        aux=skpLst->first->next[i];
        while(aux){
            printf("%d %d\n",aux->value, i);
            gravaSaidaPrint(aux->value,i);
            aux=aux->next[i];
        }
    }
}

/* função auxiliar para gravar true ou false no arquivo de saída */
void gravaSaidaStr(char nome[100]){
    FILE *arq;
    arq=fopen("saida.txt","a");
    if(arq == NULL){
        printf("Nao e possivel abrir o arquivo");
    }
    fprintf(arq,"%s",nome);
    fclose(arq);
}

/* função auxiliar para gravar a chave no arquivo de saída*/
void gravaSaidaInt(int num){
    FILE *arq;
    arq=fopen("saida.txt","a");
    if (arq == NULL){
        printf("Nao e possivel abrir o arquivo");
    }
    fprintf(arq,"%d",num);
    fclose(arq);
}

/* função auxiliar para gravar tanto a chave quanto o nível no arquivo de saída */
void gravaSaidaPrint(int num,int nivel){
    FILE *arq;
    arq=fopen("saida.txt","a");
    if (arq == NULL){
        printf("Nao e possivel abrir o arquivo");
    }
    fprintf(arq,"%d %d\n",num,nivel);
    fclose(arq);
}
