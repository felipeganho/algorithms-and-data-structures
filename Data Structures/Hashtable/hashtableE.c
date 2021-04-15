#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "hashtableE.h"

void createHT(Node *hashtable[],int sizeht){
    int i;
    for(i=0;i<sizeht;i++){
        hashtable[i]=NULL;
    }
}

Node *createNodeHT(char *inf){
    Node *ptr;
    if((ptr=(Node *)malloc(sizeof(Node)))){
        ptr->info=(char *)malloc(sizeof(char)*(strlen(inf)+1));
        strcpy(ptr->info,inf);
        ptr->proximo=NULL;
        return ptr;
    }
    return NULL;
}

int functionHT(char *inf,int sizeht){
    int i,soma=0;
    for(i=0;i<strlen(inf);i++){
        if(inf[i]<0){
            soma+=inf[i]+256;
        }
        else{
            soma+=inf[i];
        }
    }
    return fmod(soma,sizeht);
}

void insertHT(Node *hashtable[],int sizeht,char *word){
    Node *ptr=createNodeHT(word);
    int pos=functionHT(word,sizeht);
    Node *pptr=hashtable[pos];
    Node *aux=pptr;

    while(pptr){
        if(strcmp(pptr->info,word)<0){
            aux=pptr;
            pptr=pptr->proximo;
        }
        else{
            break;
        }
    }
    if(aux==pptr){
        ptr->proximo=pptr;
        hashtable[pos]=ptr;
    }
    else{
        ptr->proximo=pptr;
        aux->proximo=ptr;
    }
}

Node *mEio(Node *hashtable[],int ini,int fim,int sizeht,char *word){
    int meio;
    int pos = functionHT(word,sizeht);
    if(!hashtable[pos]) return NULL;
    Node *ptr=hashtable[pos];
    meio=(ini+fim)/2;
    for(int i=1;i<meio;i++,ptr=ptr->proximo);
    return ptr;
}

Node *searchHT(Node *hashtable[],int sizeht,char *word){
    int pos=functionHT(word,sizeht);
    Node *ptr=hashtable[pos];
    Node *aux=hashtable[pos];

    int i=0;
    while(ptr){
        i++;
        ptr=ptr->proximo;
    }

    int ini=1,meio,fim=i;
    if(!hashtable[pos] || fim==0){
        printf("Posicao da HT vazia!");
        return NULL;
    }

    if(!(aux=mEio(hashtable,ini,fim,sizeht,word))) printf("Lista vazia ou erro");

    while(ini<=fim){
        meio=(ini+fim)/2;
        if(strcmp(aux->info,word)==0){
          printf("\nEncontrou!");
          printf("%s",aux->info);
          return aux;
        }
        if(strcmp(aux->info,word)>0){
          fim=meio-1;
          printf("\n%s",aux->info);
        }
        else{
          ini=meio+1;
          printf("\n%s",aux->info);
        }
        aux=mEio(hashtable,ini,fim,sizeht,word);
    }

    printf("nao encontrou");
    return NULL;
}

void deleteHT(Node *hashtable[],int sizeht,char *word){
    Node *ptr,*aux;
    int pos = functionHT(word,sizeht);
    printf("%d",pos);
    ptr=searchHT(hashtable,sizeht,word);
    printf("%s",ptr->info);
    aux=hashtable[pos];
    printf("%s",aux->info);

    if(ptr){
      while(strcmp(aux->proximo->info,word)!=0){
        aux=aux->proximo;
      }
      aux->proximo=ptr->proximo;
      free(ptr->info);
      free(ptr);
      return;
    }
    else{
        printf("Nao ha esse elemento");
    }
}

void printHT(Node *hashtable[],int sizeht){
    int i;
    for(i=0;i<sizeht;i++){
        printf("\nIndice: %d",i);
        getchar();
        Node *ptr=hashtable[i];
        while(ptr){
            printf("\t%s",ptr->info);
            ptr=ptr->proximo;
        }
        printf("\n\n");
        getchar();
    }
}

