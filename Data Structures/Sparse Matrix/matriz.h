#ifndef __MATRIZ.H__
#define __MATRIZ.H__

typedef struct TCelula{
    struct TCelula *direita, *abaixo;
    int linha, coluna;
    double valor;
}Celula;

typedef struct{
    int linha;
    int coluna;
    Celula *inicio, *fimLinha, *fimColuna;
}matrizEsparsa;

matrizEsparsa *criaMatrizEsparsa(int linha, int coluna);

int iniciaCabecas(matrizEsparsa *matriz);

int insereCabecaLinha(matrizEsparsa *matriz);

int insereCabecaColuna(matrizEsparsa *matriz);

int insere(matrizEsparsa *matriz, int linha, int coluna, double valor);

int imprimeMatriz(matrizEsparsa *matriz);

int apagaMatriz(matrizEsparsa *matriz);

matrizEsparsa *somaMatriz(matrizEsparsa *matrizA, matrizEsparsa *matrizB, matrizEsparsa *matrizC);

matrizEsparsa *MultiplicaMatriz(matrizEsparsa *matrizA, matrizEsparsa *matrizB, matrizEsparsa *matrizC);

float obtemElementoPeloIndice(matrizEsparsa *matriz, int linha, int coluna);
#endif // __MATRIZ
