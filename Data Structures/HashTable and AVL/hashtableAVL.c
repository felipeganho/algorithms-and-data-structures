#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include "avl.c"

#define MAXSIZEHT 5
#define MAXSIZEW 23

//definição da estrutura de hashtable
typedef struct{
    int size;
    AVL *headAVL;
}SectionHash;

void createHT(SectionHash hashtable[],int sizeht){
    int i;
    for(i=0;i<sizeht;i++){
        hashtable[i].headAVL=NULL;
        hashtable[i].size=0;
    }
    return;
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

void insertHT(SectionHash hashtable[],int sizeht,char *word){
    int pos=functionHT(word,sizeht);
    insertAVL(&(hashtable[pos].headAVL),word);
    hashtable[pos].size++;
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    SectionHash hashtable[MAXSIZEHT];
    createHT(hashtable,MAXSIZEHT);

    FILE *fp=fopen("palavras1.txt","a+");
    if(fp==NULL){
        printf("Erro ao abrir o arquivo!");
        system("pause");
        return -1;
    }

    int pos,x=0;
    char aux[MAXSIZEW];
    while(!feof(fp)){
        fgets(aux,MAXSIZEW,fp);
        strtok(aux,"\n");
        pos = functionHT(aux,MAXSIZEHT);
        setlocale(LC_ALL,"Portuguese");
        printf("\nLoadDisc: Palavra=%s Posicao=%d",aux,pos);
        insertHT(hashtable,MAXSIZEHT,aux);
        x++;
    }
    printf("\nTamanho: %d",x);

    fclose(fp);

    printf("\n");

    printAVL(hashtable[2].headAVL);

//    char word[MAXSIZEW];
//    int resp,pos;
    //loadDisc(hashtable);
//    printf("\n");
//    printf("%s",hashtable[2].headAVL->info);
    //printAVL(hashtable[2].headAVL);
//    printf("%s",hashtable[0].headAVL->info);
//    printf("\n");
//    printAVL(hashtable[0].headAVL);

//    //dessa maneira funciona, mas pegando do arquivo nao
//    /** testar o seguinte código com (f C a)**/
//    printf("Digite um nome:");
//    char nome[20];
//    gets(nome);
//    insertHT(hashtable,MAXSIZEHT,nome);
//    printAVL(hashtable[2].headAVL);
//
//    printf("Insira outro:");
//    char nome2[10];
//    gets(nome2);
//    insertHT(hashtable,MAXSIZEHT,nome2);
//
//    printf("Mais uma vez:");
//    char nome3[10];
//    gets(nome3);
//    insertHT(hashtable,MAXSIZEHT,nome3);
//
//    printf("\n");
//    printAVL(hashtable[2].headAVL);
//
//    deleteAVL(hashtable[2].headAVL,nome);
//    printf("\n");
//    printAVL(hashtable[2].headAVL);
//
//    printf("\n");
//
//    AVL *aux=createAVL();
//    aux=searchAVL(hashtable[2].headAVL,nome2);
//    printf("%s",aux->info);
//
//    printf("outra vez 1: ");
//    char nome4[10];
//    gets(nome4);
//    insertHT(hashtable,MAXSIZEHT,nome4);
//
//    printf("outra vez 2: ");
//    char nome5[10];
//    gets(nome5);
//    insertHT(hashtable,MAXSIZEHT,nome5);
//
//    printf("\n");
//    printPreOrderAVL(hashtable[2].headAVL);
//    printf("%d\n",hashtable[2].size);
//
//    printf("\n");
//    printPreOrderAVL(hashtable[0].headAVL);
//    printf("%d\n",hashtable[0].size);
    return 21;
}
