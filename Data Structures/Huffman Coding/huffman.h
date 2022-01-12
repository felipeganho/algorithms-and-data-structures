/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

#ifndef huffman_H__
#define huffman_H__

//importacao de biblioteca uteis
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct no{
    struct no *dir,*esq,*pai;    //forma o no
    int contagem;                //contagem da frequencia
    char bit;                    //0 ou 1
    unsigned char caracter;      //caracter
    char *codigo;                //codificacao de Huffman
    char nbits;                  //quantidade de bits da codificacao
}no[256], *aux[256];

//variaveis globais uteis
int NSIMB, nsimb;  //numero de simbolos
FILE *f,*g;          //arquivos
int NBYTES;       //numero de bytes

//inicia estrutura, realiza contagem de caracteres e simbolos
int preProcessamento(char *arquivo);

//atribui estrutura na estrutura auxiliar
void atribuiAux();

//constroi a arvore de huffman
void arvHuffman();

//realiza a codificacao por meio de um pilha indo da folha ate a raiz
void codificar();

//imprime as informacoes de cada caracter - numero de aparicoes e a cadeia de codificacao
void imprimeInfos();

/*
    escreve cabecalho do arquivo de saidas contendo:
        1)numero de bytes do arquivo de origem
        2)numero de caracteres distintos
        3)pares de simbolo e frequencia
*/
int escreveCabecalho(char *destino);

/*
    comprime arquivo
        - varre caracter a caracter e usa a codificacao para escrever no arquivo comprimido
*/
int comprimir(char *origem, char *destino);

/*
    descomprime arquivo
        - realiza a leitura do cabecalho:
            NBYTES|NSIMB|(caracter, frequencia)
*/
int descomprimir(char *origem, char *destino);

#endif // __huffman_H__
