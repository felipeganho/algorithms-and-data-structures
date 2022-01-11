/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

//Cria AVL
AVL *criaAVL(void){
    return NULL;
}

//Pega o maior entre dois n�meros
int max(int a, int b){
    //caso a seja maior que b retorna a, sen�o retorna b
    return (a > b) ? a : b;
}

//Cria um n�
AVL *criaNoAVL(void *info){
    //aloca n� e faz apontamentos de esquerda, direita, info e altura recebe 1
    AVL *no = (AVL *)malloc(sizeof(AVL));
    no->info = info;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

//Retorna a sub-�rvore esquerda
AVL *esquerdaAVL(AVL *avl){
    if(vaziaAVL(avl))return NULL;
    return avl->esquerda;
}

//Retorna a sub-�rvore direita
AVL *direitaAVL(AVL *avl){
    if(vaziaAVL(avl))return NULL;
    return avl->direita;
}

//Verifica se a �rvore � nula
int vaziaAVL(AVL *avl){
    //caso seja nulo retorna 1 sen�o 0
    return (!avl);
}

//Busca um elemento na �rvore AVL
AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *)){
    if(!avl){
        printf("\nNao e possivel buscar -> Aluno nao existe!\n");
        return NULL;
    }
    //caso seja o elemento encontra retorna-o
    if(comp(inf, avl->info) == 0) return avl;
    //caso o elemento seja menor que a chave da �rvore AVL desce � esquerda
    else if(comp(inf, avl->info) == 1) return buscaAVL(esquerdaAVL(avl),inf, comp);
    //caso o elemento seja maior que a chave da �rvore AVL desce � direita
    else return buscaAVL(direitaAVL(avl),inf, comp);
}

//Calcula a altura da �rvore
int alturaAVL(AVL *avl){
    if (!avl) return 0;
    return avl->altura;
}

//Rotac�o � direita
AVL *rotacaoDireita(AVL *avl){
    AVL *x = avl->esquerda;
    AVL *y = x->direita;

    x->direita = avl;
    avl->esquerda = y;

    avl->altura = max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl))) + 1;
    x->altura = max(alturaAVL(esquerdaAVL(x)), alturaAVL(direitaAVL(x))) + 1;

    return x;
}

//Rotac�o � esquerdaAVL
AVL *rotacaoEsquerda(AVL *avl){
    AVL *y = avl->direita;
    AVL *x = y->esquerda;

    y->esquerda = avl;
    avl->direita = x;

    avl->altura = max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl))) + 1;
    y->altura = max(alturaAVL(esquerdaAVL(y)), alturaAVL(direitaAVL(y))) + 1;
    return y;
}

//Retorna o fator de balan�o do n�
int fatorBalanco(AVL *avl) {
    if (!avl) return 0;
    //diferen�a entre a altura da sub-�rvore esquerda menos a altura da sub-�rvore direita
    return alturaAVL(esquerdaAVL(avl)) - alturaAVL(direitaAVL(avl));
}

//Insere um novo n� na �rvore AVL
AVL *insereAVL(AVL *avl, void *info, int(*comp)(void *, void *)){
    //Encontra a posi��o correta de inser��o e o insere

    //caso seja nulo cria outro n�
    if (!avl)
        return criaNoAVL(info);

    //caso a chave seja menor que a chave do n� da �rvore
    if(comp(info, avl->info) == 1)
        avl->esquerda = insereAVL(esquerdaAVL(avl), info, comp);

    //caso a chave seja menor que a chave do n� da �rvore
    else if (comp(info, avl->info) == -1)
        avl->direita = insereAVL(direitaAVL(avl), info, comp);

    //caso a chave seja igual a chave do n� da �rvore
    else
        return avl;

    //Atualiza o fator de balan�o de cada n� e balanceia a �rvore
    avl->altura = 1 + max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl)));

    //Obt�m o fator de balan�o do n�
    int balanco = fatorBalanco(avl);

    //Rota��o Simples � Direita
    if (balanco > 1 && comp(info, avl->esquerda->info) == 1){
       return rotacaoDireita(avl);
    }

    //Rota��o Simples � Esquerda
    if (balanco < -1 && comp(info, avl->direita->info) == -1){
      return rotacaoEsquerda(avl);
    }

    //Rota��o Dupla � Direita
    if (balanco > 1 && comp(info, avl->esquerda->info) == -1){
        avl->esquerda = rotacaoEsquerda(avl->esquerda);
        return rotacaoDireita(avl);
    }

    //Rota��o Dupla � Esquerda
    if (balanco < -1 && comp(info, avl->direita->info) == 1){
        avl->direita = rotacaoDireita(avl->direita);
        return rotacaoEsquerda(avl);
    }

    return avl;
}

//Retorna o menor valor da �rvore AVL
AVL *menorValor(AVL *avl){
    AVL *atual = avl;

    //Percorre enquanto houver elemento � esquerda no n�
    while (atual->esquerda)
        atual = atual->esquerda;

    return atual;
}

//Delete um n� da arv�re AVL
AVL *deletaAVL(AVL *avl, void *info, int(*comp)(void *, void *)){
    //Encontra o n� e deleta-o

    //caso seja nulo retorna ele pr�prio
    if (!avl){
        printf("\nNao e possivel deletar -> Aluno nao existe!\n");
        return avl;
    }

    //caso a chave seja menor que a chave do n� da �rvore
    if (comp(info, avl->info) == 1)
        avl->esquerda = deletaAVL(esquerdaAVL(avl), info, comp);

    //caso a chave seja menor que a chave do n� da �rvore
    else if (comp(info, avl->info) == -1)
        avl->direita = deletaAVL(direitaAVL(avl), info, comp);

    //caso a chave seja igual a chave do n� da �rvore
    else{
        //caso alguma sub-�rvore seja nula
        if ((!esquerdaAVL(avl)) || (!direitaAVL(avl))){
          AVL *temp = esquerdaAVL(avl) ? esquerdaAVL(avl) : direitaAVL(avl);

          if (!temp){
            temp = avl;
            avl = NULL;
          }

          else
            *avl = *temp;

          free(temp);
        }

        //caso nenhuma sub-�rvore seja nula
        else {
          AVL *temp = menorValor(direitaAVL(avl));
          avl->info = temp->info;
          avl->direita = deletaAVL(direitaAVL(avl), temp->info, comp);
        }
    }

    if (!avl)
        return avl;

    //Atualiza o fator de balan�o de cada n� e balanceia a �rvore
    avl->altura = 1 + max(alturaAVL(avl->esquerda), alturaAVL(avl->direita));

    //Obt�m o fator de balan�o do n�
    int balanco = fatorBalanco(avl);

    //Rota��o Simples � Direita
    if (balanco > 1 && fatorBalanco(avl->esquerda) >= 0)
        return rotacaoDireita(avl);

    //Rota��o Dupla � Direita
    if (balanco > 1 && fatorBalanco(avl->esquerda) < 0){
        avl->esquerda = rotacaoEsquerda(avl->esquerda);
        return rotacaoDireita(avl);
    }

    //Rota��o Simples � Esquerda
    if (balanco < -1 && fatorBalanco(avl->direita) <= 0)
        return rotacaoEsquerda(avl);

    //Rota��o Dupla � Esquerda
    if (balanco < -1 && fatorBalanco(avl->direita) > 0){
        avl->direita = rotacaoDireita(avl->direita);
        return rotacaoEsquerda(avl);
    }

    return avl;
}

//Impress�o da �rvore na sequ�ncia pr�-ordem
void printPreOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        imprime(avl);
        printPreOrdem(avl->esquerda, imprime);
        printPreOrdem(avl->direita, imprime);
    }
}

//Impress�o da �rvore na sequ�ncia em ordem
void printEmOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        printEmOrdem(avl->esquerda, imprime);
        imprime(avl);
        printEmOrdem(avl->direita, imprime);
    }
}

//Impress�o da �rvore na sequ�ncia p�s-ordem
void printPosOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        printPosOrdem(avl->esquerda, imprime);
        printPosOrdem(avl->direita, imprime);
        imprime(avl);
    }
}
