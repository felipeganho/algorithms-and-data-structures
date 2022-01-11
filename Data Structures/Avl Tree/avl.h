/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

#ifndef __AVL_H__
#define __AVL_H__

//Estrutura utilizada para tipo gen�rico de dados
typedef struct avlno{
  void *info;
  struct avlno *esquerda;
  struct avlno *direita;
  int altura;
}AVL;

/* funcao: AVL *criaAVL()
   *  acao:        funcao que cria uma AVL
   *  entrada:     void
   *  saida:       ponteiro para uma AVL
   *  suposicoes:  nenhuma
*/
AVL *criaAVL(void);

/* funcao: int max(int a, int b)
   *  acao:        funcao que verifica o maior entre dois n�meros
   *  entrada:     inteiro a e inteiro b
   *  saida:       maior inteiro entre a e b
   *  suposicoes:  nenhuma
*/
int max(int a, int b);

/* funcao: Node *criaNoAVL()
   *  acao:        funcao que cria um novo no qual dever� ser inserido na arvore
   *  entrada:     elemento de informacao do novo n�
   *  saida:       ponteiro para um n�
   *  suposicoes:  nenhuma
*/
AVL *criaNoAVL(void *info);

/* funcao: AVL *esquerdaAVL(AVL *avl)
   *  acao:        retorna a sub�rvore esquerda de uma �rvore avl
   *  entrada:     ponteiro para a �rvore avl (avl)
   *  saida:       ponteiro para a sub�rvore esquerda de avl
   *  suposicoes:  �rvore avl
*/
AVL *esquerdaAVL(AVL *avl);

/* funcao: AVL *direitaAVL(AVL *avl)
   *  acao:        retorna a sub�rvore direita de uma �rvore avl
   *  entrada:     ponteiro para a �rvore avl (avl)
   *  saida:       ponteiro para a sub�rvore direita de avl
   *  suposicoes:  �rvore avl
*/
AVL *direitaAVL(AVL *avl);

/* funcao: int vaziaAVL(AVL *avl)
   *  acao:        verifica se uma �rvore avl esta vazia ou nula
   *  entrada:     ponteiro para a �rvore avl (avl)
   *  saida:       1, se a arvore avl � vazia ou nula
				   0, caso contrario
   *  suposicoes:  �rvore avl
*/
int vaziaAVL(AVL *avl);

/* funcao: AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *))
   *  acao:        busca por um elemento de informa��o na �rvore AVL
   *  entrada:     ponteiro para a �rvore AVL (avl), um ponteiro para o elemento de informa��o (inf)
                   e um fun��o de callback para comparar a chave da �rvore (comp)
   *  saida:       ponteiro para o n� da �rvore que cont�m o elemento de informa��o buscado
				   NULL, caso contrario
   *  suposicoes:  �rvore avl
*/
AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *));

/* funcao: int alturaAVL(int a, int b)
   *  acao:        funcao que retorna a altura da �rvore AVL
   *  entrada:     inteiro a e inteiro b
   *  saida:       altura da �rvore AVL
   *  suposicoes:  nenhuma
*/
int alturaAVL(AVL *avl);

/* funcao: int *rotacaoDireita(AVL *avl)
   *  acao:        rotaciona uma �rvore AVL � direita
   *  entrada:     ponteiro para AVL rotacionada
   *  saida:       ponteiro para uma AVL
   *  suposicoes:  nenhuma
*/
AVL *rotacaoDireita(AVL *avl);

/* funcao: int *rotacaoEsquerda(AVL *avl)
   *  acao:        rotaciona uma �rvore AVL � esquerda
   *  entrada:     ponteiro para AVL
   *  saida:       ponteiro para uma AVL rotacionada
   *  suposicoes:  nenhuma
*/
AVL *rotacaoEsquerda(AVL *avl);

/* funcao: int fatorBalanco(AVL *avl)
   *  acao:        funcao que retorna o fator de balan�o da �rvore AVL
   *  entrada:     ponteiro para uma �rvore AVL
   *  saida:       fator de balan�o da �rvore AVL
   *  suposicoes:  nenhuma
*/
int fatorBalanco(AVL *avl);

/* funcao: AVL *insereAVL(AVL *avl,void *info, int(*comp)(void *, void *))
   *  acao:        insere um novo n� na �rvore AVL
   *  entrada:     ponteiro para a �rvore avl (avl), um ponteiro para o elemento de informa��o a ser inserido (inf)
                e um fun��o de callback para comparar a chave da �rvore (comp)
   *  saida:		1, caso a inser��o ocorra com sucesso
   					0, caso contrario
   *  suposicoes:  �rvore avl
*/
AVL *insereAVL(AVL *avl, void *info, int(*comp)(void *, void *));

/* funcao: AVL *menorValor(AVL *avl)
   *  acao:        retorna o menor elemento da �rvore AVL
   *  entrada:     ponteiro para a �rvore avl (avl)
   *  saida:	    ponteiro para o menor elemento da �rvore
   *  suposicoes:  �rvore avl
*/
AVL *menorValor(AVL *avl);

/* funcao: AVL *deletaAVL(AVL *avl,void *info, int(*comp)(void *, void *))
   *  acao:        insere um novo n� na �rvore AVL
   *  entrada:     ponteiro para a �rvore avl (avl), um ponteiro para o elemento de informa��o a ser inserido (inf)
                e um fun��o de callback para comparar a chave da �rvore (comp)
   *  saida:		1, caso a inser��o ocorra com sucesso
   					0, caso contrario
   *  suposicoes:  �rvore avl
*/
AVL *deletaAVL(AVL *avl, void *info, int(*comp)(void *, void *));

/* funcao: void printPreOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informa��o considerando o caminho em pr�-ordem da �rvore AVL
   *  entrada:     ponteiro para a �rvore avl e uma fun��o de callback para imprimir o conte�do
   *  saida:       void
   *  suposicoes:  �rvore avl
*/
void printPreOrdem(AVL *avl, void(*imprime)(AVL *));

/* funcao: void printEmOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informa��o considerando o caminho em ordem da �rvore AVL
   *  entrada:     ponteiro para a �rvore avl e uma fun��o de callback para imprimir o conte�do
   *  saida:       void
   *  suposicoes:  �rvore avl
*/
void printEmOrdem(AVL *avl, void(*imprime)(AVL *));

/* funcao: void printPosOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informa��o considerando o caminho p�s-ordem da �rvore AVL
   *  entrada:     ponteiro para a �rvore avl e uma fun��o de callback para imprimir o conte�do
   *  saida:       void
   *  suposicoes:  �rvore avl
*/
void printPosOrdem(AVL *avl, void(*imprime)(AVL *));

#endif // __AVL_H__
