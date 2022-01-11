/*
    Integrantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

//arquivos de cabecalho
#ifndef treeRN__H__
#define treeRN__H__

//inclusao de bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//definicao das cores
enum Cor {RED, BLACK};
typedef enum Cor TipoCor;

//definicao da estrutura de artigo
typedef struct Artigo *artigo;
typedef struct Artigo {
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[20];
    char palavraChave[200];
}Artigo;

//definicao da arvore rubro-negra
typedef struct No *arvoreRN;
typedef struct No {
    Artigo *artigo;
    TipoCor cor;
    arvoreRN pai;
    arvoreRN esq, dir;
}No;

//variaveis globais
arvoreRN raiz, noNullRN;

//cria artigo com seus respectivos campos
Artigo *criaArtigo(Artigo *artigo);

//mostra dados do artigo
void mostrarArtigo(Artigo *artigo);

//aloca memoria para um novo no da arvore rubro-negra
arvoreRN criaNoRN(Artigo *artigo, arvoreRN esq, arvoreRN dir, arvoreRN pai);

//aloca memoria para as variaveis globais
void iniciaRN(void);

//rotacao a esquerda
arvoreRN rotacaoEsquerda(arvoreRN T, arvoreRN w);

//rotacao a direita
arvoreRN rotacaoDireita(arvoreRN T, arvoreRN w);

//conserta as cores apos insercao de um novo no na arvore rubro-negra
arvoreRN consertaInsereRN(arvoreRN T, arvoreRN w);

//insere um novo no na arvore rubro-negra
arvoreRN insereRN(arvoreRN w, Artigo *artigo);

//Retorna a altura da arvore
int altura(arvoreRN w);

//imprime no's por nivel
void auximprimeNivelRN(arvoreRN w, int nivel);

//Imprime a arvore por nivel
void imprimeNivelRN(arvoreRN w);

//Imprime a arvore em ordem
void imprimeEmOrdemRN(arvoreRN w);

//Retorna arvore mais a esqquerda do filho a direita
arvoreRN sucessorRN(arvoreRN w);

//conserta as cores apos remocao de um no na arvore rubro-negra
void consertaRemoveRN(arvoreRN T, arvoreRN w);

//remove um no da arvore rubro-negra
void removeRN(arvoreRN T, arvoreRN w);

//busca por no com id
arvoreRN buscaRN(arvoreRN w, int id);

#endif
