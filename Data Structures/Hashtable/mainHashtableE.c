#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "hashtableE.c"
#include <conio.h>
#include <locale.h>

#define MAXSIZEHT 5
#define MAXSIZEW 23

int loadDisc(Node *hashtable[]){
    FILE *fp=fopen("palavras.txt","a+");
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
    return 1;
}

int main(){
    setlocale(LC_ALL,"Portuguese");
    Node *hashtable[MAXSIZEHT];
    char word[MAXSIZEW];
    int resp,pos;

    createHT(hashtable,MAXSIZEHT);
    loadDisc(hashtable);
    do{
        printf("\nDigite a palavra a ser buscada: ");
        fflush(stdin);
        gets(word);
        pos = functionHT(word,MAXSIZEHT);
        printf("\nPalavra: %s Posicao: %d",word,pos);
        searchHT(hashtable,MAXSIZEHT,word);
        printf("\nBuscar mais? 1-SIM ou 2-NAO");
        scanf("%d",&resp);
    }while(resp==1);

    getchar();
    printHT(hashtable,MAXSIZEHT);
    return 0;

    char nome[20];
    scanf("%s",nome);
    functionHT(nome,5);

    /*
    char nome[10];
    nome[0]='á';
    nome[1]='\0';
    int i,soma=0;

    //gets(nome);
    for(i=0;nome[i]!='\0';i++){
        soma+=nome[i];
    }
    printf("%d",soma);
    */

}
