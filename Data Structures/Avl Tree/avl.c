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

//Pega o maior entre dois números
int max(int a, int b){
    //caso a seja maior que b retorna a, senão retorna b
    return (a > b) ? a : b;
}

//Cria um nó
AVL *criaNoAVL(void *info){
    //aloca nó e faz apontamentos de esquerda, direita, info e altura recebe 1
    AVL *no = (AVL *)malloc(sizeof(AVL));
    no->info = info;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

//Retorna a sub-árvore esquerda
AVL *esquerdaAVL(AVL *avl){
    if(vaziaAVL(avl))return NULL;
    return avl->esquerda;
}

//Retorna a sub-árvore direita
AVL *direitaAVL(AVL *avl){
    if(vaziaAVL(avl))return NULL;
    return avl->direita;
}

//Verifica se a árvore é nula
int vaziaAVL(AVL *avl){
    //caso seja nulo retorna 1 senão 0
    return (!avl);
}

//Busca um elemento na árvore AVL
AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *)){
    if(!avl){
        printf("\nNao e possivel buscar -> Aluno nao existe!\n");
        return NULL;
    }
    //caso seja o elemento encontra retorna-o
    if(comp(inf, avl->info) == 0) return avl;
    //caso o elemento seja menor que a chave da árvore AVL desce à esquerda
    else if(comp(inf, avl->info) == 1) return buscaAVL(esquerdaAVL(avl),inf, comp);
    //caso o elemento seja maior que a chave da árvore AVL desce à direita
    else return buscaAVL(direitaAVL(avl),inf, comp);
}

//Calcula a altura da árvore
int alturaAVL(AVL *avl){
    if (!avl) return 0;
    return avl->altura;
}

//Rotacão à direita
AVL *rotacaoDireita(AVL *avl){
    AVL *x = avl->esquerda;
    AVL *y = x->direita;

    x->direita = avl;
    avl->esquerda = y;

    avl->altura = max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl))) + 1;
    x->altura = max(alturaAVL(esquerdaAVL(x)), alturaAVL(direitaAVL(x))) + 1;

    return x;
}

//Rotacão à esquerdaAVL
AVL *rotacaoEsquerda(AVL *avl){
    AVL *y = avl->direita;
    AVL *x = y->esquerda;

    y->esquerda = avl;
    avl->direita = x;

    avl->altura = max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl))) + 1;
    y->altura = max(alturaAVL(esquerdaAVL(y)), alturaAVL(direitaAVL(y))) + 1;
    return y;
}

//Retorna o fator de balanço do nó
int fatorBalanco(AVL *avl) {
    if (!avl) return 0;
    //diferença entre a altura da sub-árvore esquerda menos a altura da sub-árvore direita
    return alturaAVL(esquerdaAVL(avl)) - alturaAVL(direitaAVL(avl));
}

//Insere um novo nó na árvore AVL
AVL *insereAVL(AVL *avl, void *info, int(*comp)(void *, void *)){
    //Encontra a posição correta de inserção e o insere

    //caso seja nulo cria outro nó
    if (!avl)
        return criaNoAVL(info);

    //caso a chave seja menor que a chave do nó da árvore
    if(comp(info, avl->info) == 1)
        avl->esquerda = insereAVL(esquerdaAVL(avl), info, comp);

    //caso a chave seja menor que a chave do nó da árvore
    else if (comp(info, avl->info) == -1)
        avl->direita = insereAVL(direitaAVL(avl), info, comp);

    //caso a chave seja igual a chave do nó da árvore
    else
        return avl;

    //Atualiza o fator de balanço de cada nó e balanceia a árvore
    avl->altura = 1 + max(alturaAVL(esquerdaAVL(avl)), alturaAVL(direitaAVL(avl)));

    //Obtém o fator de balanço do nó
    int balanco = fatorBalanco(avl);

    //Rotação Simples à Direita
    if (balanco > 1 && comp(info, avl->esquerda->info) == 1){
       return rotacaoDireita(avl);
    }

    //Rotação Simples à Esquerda
    if (balanco < -1 && comp(info, avl->direita->info) == -1){
      return rotacaoEsquerda(avl);
    }

    //Rotação Dupla à Direita
    if (balanco > 1 && comp(info, avl->esquerda->info) == -1){
        avl->esquerda = rotacaoEsquerda(avl->esquerda);
        return rotacaoDireita(avl);
    }

    //Rotação Dupla à Esquerda
    if (balanco < -1 && comp(info, avl->direita->info) == 1){
        avl->direita = rotacaoDireita(avl->direita);
        return rotacaoEsquerda(avl);
    }

    return avl;
}

//Retorna o menor valor da árvore AVL
AVL *menorValor(AVL *avl){
    AVL *atual = avl;

    //Percorre enquanto houver elemento à esquerda no nó
    while (atual->esquerda)
        atual = atual->esquerda;

    return atual;
}

//Delete um nó da arvóre AVL
AVL *deletaAVL(AVL *avl, void *info, int(*comp)(void *, void *)){
    //Encontra o nó e deleta-o

    //caso seja nulo retorna ele próprio
    if (!avl){
        printf("\nNao e possivel deletar -> Aluno nao existe!\n");
        return avl;
    }

    //caso a chave seja menor que a chave do nó da árvore
    if (comp(info, avl->info) == 1)
        avl->esquerda = deletaAVL(esquerdaAVL(avl), info, comp);

    //caso a chave seja menor que a chave do nó da árvore
    else if (comp(info, avl->info) == -1)
        avl->direita = deletaAVL(direitaAVL(avl), info, comp);

    //caso a chave seja igual a chave do nó da árvore
    else{
        //caso alguma sub-árvore seja nula
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

        //caso nenhuma sub-árvore seja nula
        else {
          AVL *temp = menorValor(direitaAVL(avl));
          avl->info = temp->info;
          avl->direita = deletaAVL(direitaAVL(avl), temp->info, comp);
        }
    }

    if (!avl)
        return avl;

    //Atualiza o fator de balanço de cada nó e balanceia a árvore
    avl->altura = 1 + max(alturaAVL(avl->esquerda), alturaAVL(avl->direita));

    //Obtém o fator de balanço do nó
    int balanco = fatorBalanco(avl);

    //Rotação Simples à Direita
    if (balanco > 1 && fatorBalanco(avl->esquerda) >= 0)
        return rotacaoDireita(avl);

    //Rotação Dupla à Direita
    if (balanco > 1 && fatorBalanco(avl->esquerda) < 0){
        avl->esquerda = rotacaoEsquerda(avl->esquerda);
        return rotacaoDireita(avl);
    }

    //Rotação Simples à Esquerda
    if (balanco < -1 && fatorBalanco(avl->direita) <= 0)
        return rotacaoEsquerda(avl);

    //Rotação Dupla à Esquerda
    if (balanco < -1 && fatorBalanco(avl->direita) > 0){
        avl->direita = rotacaoDireita(avl->direita);
        return rotacaoEsquerda(avl);
    }

    return avl;
}

//Impressão da árvore na sequência pré-ordem
void printPreOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        imprime(avl);
        printPreOrdem(avl->esquerda, imprime);
        printPreOrdem(avl->direita, imprime);
    }
}

//Impressão da árvore na sequência em ordem
void printEmOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        printEmOrdem(avl->esquerda, imprime);
        imprime(avl);
        printEmOrdem(avl->direita, imprime);
    }
}

//Impressão da árvore na sequência pós-ordem
void printPosOrdem(AVL *avl, void(*imprime)(AVL *)){
    if (avl){
        printPosOrdem(avl->esquerda, imprime);
        printPosOrdem(avl->direita, imprime);
        imprime(avl);
    }
}
