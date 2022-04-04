#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matriz.h"

matrizEsparsa *criaMatrizEsparsa(int linha, int coluna){
    matrizEsparsa *matriz;
    matriz=(matrizEsparsa *)malloc(sizeof(matrizEsparsa));

    if(!matriz || linha<=0 || coluna <=0){
        return 0;
    }

    matriz->inicio=NULL;
    matriz->fimLinha=NULL;
    matriz->fimColuna=NULL;
    matriz->linha=linha;
    matriz->coluna=coluna;

    iniciaCabecas(matriz);

    return matriz;
}

int iniciaCabecas(matrizEsparsa *matriz){
    int i=0;

    Celula *cabeca;
    cabeca=(Celula *)malloc(sizeof(Celula));

    if(!cabeca){
        return 0;
    }

    cabeca->coluna=-1;
    cabeca->linha=-1;

    matriz->inicio=cabeca;
    matriz->fimLinha=cabeca;
    matriz->fimColuna=cabeca;

    for(i=1; i<= matriz->coluna; i++){
        insereCabecaColuna(matriz);
    }

    for(i=1; i<= matriz->linha; i++){
        insereCabecaLinha(matriz);
    }

    return 1;
}

int insereCabecaColuna(matrizEsparsa *matriz){
    Celula *cabeca;
    cabeca = (Celula *)malloc(sizeof(Celula));

    if(!cabeca) return 0;

    cabeca->coluna = -1;
    cabeca->linha = 0;

    matriz->fimColuna->direita=cabeca;
    matriz->fimColuna=cabeca;

    cabeca->direita=matriz->inicio;
    cabeca->abaixo=cabeca;

    return 1;
}

int insereCabecaLinha(matrizEsparsa *matriz){
    Celula *cabeca;
    cabeca = (Celula *)malloc(sizeof(Celula));

    if(!cabeca) return 0;

    cabeca->coluna = 0;
    cabeca->linha = -1;

    matriz->fimLinha->abaixo = cabeca;
    matriz->fimLinha = cabeca;

    cabeca->abaixo = matriz->inicio;
    cabeca->direita = cabeca;

    return 1;
}

int insere(matrizEsparsa *matriz, int linha, int coluna, double valor){
    int i;

    if (!matriz || matriz->linha <= 0 || matriz->coluna <= 0 || !valor){ //esses testes sao feitos tbm na funcao lerMatriz
        return 0;
    }
    if (linha>matriz->linha || coluna>matriz->coluna || !valor || linha < 1 || coluna < 1){
        return 0;
    }

    Celula *celula; //celula temporaria
    Celula *celulaColuna; //celula temporaria para coluna
    Celula *celulaLinha; //celula temporaria para linha

    celula = (Celula*)malloc(sizeof(Celula));

    if (!celula){ //memoria cheia
        return 0;
    }

    celula->linha = linha;
    celula->coluna = coluna;
    celula->valor = valor;

    celulaLinha = matriz->inicio->abaixo; //linha aponta para a primeira cabeca so de linha
    celulaColuna = matriz->inicio->direita; //linha aponta para a primeira cabeca so de coluna

    //Percorre ate a linha do elemento, percorre nas cabecas ate a informada
    for (i=0; i<linha-1; i++){ //-1 pq ja ta na primeira
        celulaLinha = celulaLinha->abaixo; //percorre para baixo(linhas) ate achar a correta
    }
    i=0;
    while (i<coluna && celulaLinha->direita->linha != -1){
        if (celulaLinha->direita->coluna > celula->coluna){ //se a celula inserida esta a esquerda
            celula->direita = celulaLinha->direita;
            celulaLinha->direita = celula;
        }
        else{
            celulaLinha= celulaLinha->direita; //anda pelas celulas a direita
        }
        i++;
    }
    if (celulaLinha->direita->linha == -1){ //a celula esta mais a direita
        celula->direita = celulaLinha->direita; //aponta para a cabeca
        celulaLinha->direita = celula; //ultima celula ou cabeca, senao tiver celulas, aponta para a celula
    }
    //linha encontrada e apontada

    //Agora vamos encontrar a coluna
    //Percorre ate a coluna do elemento, percorre nas cabecas ate a informada
    for (i = 0; i < coluna-1; i++){ //-1 pq ja ta na primeira
        celulaColuna = celulaColuna->direita; //percorre a direita (colunas) ate achar a correta
    }
    i=0;
    while (i<linha && celulaColuna->abaixo->coluna != -1){ //anda pelas celulas ate achar a posicao
        if (celulaColuna->abaixo->linha > celula->linha){
            celula->abaixo = celulaColuna->abaixo;
            celulaColuna->abaixo = celula;
        }
        else{
            celulaColuna = celulaColuna->abaixo; //anda pelas celulas abaixo
        }
        i++;
    }
    if (celulaColuna->abaixo->coluna == -1){
        celula->abaixo = celulaColuna->abaixo; //aponta para a cabeca
        celulaColuna->abaixo = celula; //ultima celula ou cabeca, senao tiver celulas, aponta para a celula
    }
    return 1;
}

int imprimeMatriz(matrizEsparsa *matriz){

    int i, j;
    Celula *celula;

    if (!matriz || !matriz->linha || !matriz->coluna){
        return 0;
    }

    celula = matriz->inicio->abaixo;

    printf("\n");

    for (i = 1; i <= matriz->linha; i++){
        for (j = 1; j <= matriz->coluna; j++){
            if (celula->direita->linha == i && celula->direita->coluna == j){
                celula = celula->direita;
                printf("  \t%0.2f   ", celula->valor);
            }
            else{
                printf("  \t%0.2f   ", 0.0F);
            }
        }
        printf("\n");
        celula = celula->direita->abaixo;
    }

    return 1;
}

int apagaMatriz(matrizEsparsa *matriz){
    int i = 1;
    int j = 1;
    Celula *celula, *aux;

    if (!matriz || !matriz->linha || !matriz->coluna){
        return 0;
    }

    celula = matriz->inicio->abaixo;
    celula = celula->direita;

    for (i = 1; i <= matriz->linha; i++){
        for (j = 1; j <= matriz->coluna; j++){
            if (celula->linha == i && celula->coluna == j){
                aux = celula;
                celula= celula->direita;
                free(aux);
            }
        }
        celula = celula->abaixo->direita;
    }

    //apaga cabecas
    celula= matriz->inicio->direita;

    for (i = 0; i < matriz->coluna; i++){ //cabecas coluna
        aux = celula;
        celula = celula->direita;
        free(aux);
    }

    celula= matriz->inicio->abaixo;
    for (i = 0; i < matriz->linha; i++){ //cabecas linha
        aux = celula;
        celula= celula->abaixo;
        free(aux);
    }

    celula= matriz->inicio;
    free(celula);

    matriz->fimColuna= matriz->fimLinha = matriz->inicio = NULL;
    matriz->linha = matriz->coluna = 0;
    matriz = NULL;

    return 1;
}

matrizEsparsa *somaMatriz(matrizEsparsa *matrizA, matrizEsparsa *matrizB, matrizEsparsa *matrizC){
    int i, j;
    float soma;
    Celula *celula1, *celula2;

    if (matrizA->linha != matrizB->linha || matrizA->coluna != matrizB->coluna){ //soma de matrizes so é possivel qndo as duas forem de mesma ordem
        printf("\n So e possivel somar matrizes de mesma ordem");
        return NULL;
    }

    if (!matrizA || !matrizB|| !matrizA->linha || !matrizA->coluna){
        return NULL;
    }

    celula1 = matrizA->inicio->abaixo;
    celula2 = matrizB->inicio->abaixo;

    for (i = 1; i <= matrizA->linha; i++){
        for (j = 1; j <= matrizA->coluna; j++){
            if (j == celula1->direita->coluna && j == celula2->direita->coluna){
                soma = celula1->direita->valor + celula2->direita->valor;
                if (soma){
                    insere(matrizC, i, j, soma);
                }
                celula1 = celula1->direita;
                celula2 = celula2->direita;
            }
            else if (j == celula1->direita->coluna){
                insere(matrizC, i, j, celula1->direita->valor);
                celula1= celula1->direita;
            }
            else if (j == celula2->direita->coluna){
                insere(matrizC, i, j, celula2->direita->valor);
                celula2 = celula2->direita;
            }
        }
        celula1 = celula1->direita->abaixo;
        celula2 = celula2->direita->abaixo;
    }

    return matrizC;
}

matrizEsparsa *MultiplicaMatriz(matrizEsparsa *matrizA, matrizEsparsa *matrizB, matrizEsparsa *matrizC){
    int i=0, j=0, k=0;
    float total;

    if (matrizA->coluna != matrizB->linha){ //so pode multiplicar se o numero de colunas de A eh igual ao numero de linhas de B
        printf("\nO numero de linhas e diferente do numero de colunas");
        return NULL;
    }

    if (!matrizA || !matrizB || !matrizA->linha || !matrizA->coluna || !matrizB->coluna){
        return NULL;
    }

    for (i = 1; i <= matrizA->linha; i++){
        for (j = 1; j <= matrizB->coluna; j++){
            total = 0;
            for (k = 1; k <= matrizA->coluna; k++){
                total += obtemElementoPeloIndice(matrizA,i,k) * obtemElementoPeloIndice(matrizB,k,j);
            }
            if (total){
                insere(matrizC,i,j,total);
            }
        }
    }
    return matrizC;
}

float obtemElementoPeloIndice(matrizEsparsa *matriz, int linha, int coluna){
    Celula *celula;
    int i = 0;

    celula = matriz->inicio->direita;

    for (i = 0; i < coluna-1; i++){ //chega na coluna desejada
        celula = celula->direita;
    }

    do{
        celula = celula->abaixo;
        if (celula->linha == linha){
            return celula->valor;
        }
    }while(celula->coluna != -1);

    return 0; //elemento nao encontrado
}
