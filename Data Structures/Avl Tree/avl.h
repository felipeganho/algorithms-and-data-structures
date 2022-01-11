/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

#ifndef __AVL_H__
#define __AVL_H__

//Estrutura utilizada para tipo genérico de dados
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
   *  acao:        funcao que verifica o maior entre dois números
   *  entrada:     inteiro a e inteiro b
   *  saida:       maior inteiro entre a e b
   *  suposicoes:  nenhuma
*/
int max(int a, int b);

/* funcao: Node *criaNoAVL()
   *  acao:        funcao que cria um novo no qual deverá ser inserido na arvore
   *  entrada:     elemento de informacao do novo nó
   *  saida:       ponteiro para um nó
   *  suposicoes:  nenhuma
*/
AVL *criaNoAVL(void *info);

/* funcao: AVL *esquerdaAVL(AVL *avl)
   *  acao:        retorna a subárvore esquerda de uma árvore avl
   *  entrada:     ponteiro para a árvore avl (avl)
   *  saida:       ponteiro para a subárvore esquerda de avl
   *  suposicoes:  árvore avl
*/
AVL *esquerdaAVL(AVL *avl);

/* funcao: AVL *direitaAVL(AVL *avl)
   *  acao:        retorna a subárvore direita de uma árvore avl
   *  entrada:     ponteiro para a árvore avl (avl)
   *  saida:       ponteiro para a subárvore direita de avl
   *  suposicoes:  árvore avl
*/
AVL *direitaAVL(AVL *avl);

/* funcao: int vaziaAVL(AVL *avl)
   *  acao:        verifica se uma árvore avl esta vazia ou nula
   *  entrada:     ponteiro para a árvore avl (avl)
   *  saida:       1, se a arvore avl é vazia ou nula
				   0, caso contrario
   *  suposicoes:  árvore avl
*/
int vaziaAVL(AVL *avl);

/* funcao: AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *))
   *  acao:        busca por um elemento de informação na árvore AVL
   *  entrada:     ponteiro para a árvore AVL (avl), um ponteiro para o elemento de informação (inf)
                   e um função de callback para comparar a chave da árvore (comp)
   *  saida:       ponteiro para o nó da árvore que contém o elemento de informação buscado
				   NULL, caso contrario
   *  suposicoes:  árvore avl
*/
AVL *buscaAVL(AVL *avl, void *inf, int (*comp)(void *, void *));

/* funcao: int alturaAVL(int a, int b)
   *  acao:        funcao que retorna a altura da árvore AVL
   *  entrada:     inteiro a e inteiro b
   *  saida:       altura da árvore AVL
   *  suposicoes:  nenhuma
*/
int alturaAVL(AVL *avl);

/* funcao: int *rotacaoDireita(AVL *avl)
   *  acao:        rotaciona uma árvore AVL à direita
   *  entrada:     ponteiro para AVL rotacionada
   *  saida:       ponteiro para uma AVL
   *  suposicoes:  nenhuma
*/
AVL *rotacaoDireita(AVL *avl);

/* funcao: int *rotacaoEsquerda(AVL *avl)
   *  acao:        rotaciona uma árvore AVL à esquerda
   *  entrada:     ponteiro para AVL
   *  saida:       ponteiro para uma AVL rotacionada
   *  suposicoes:  nenhuma
*/
AVL *rotacaoEsquerda(AVL *avl);

/* funcao: int fatorBalanco(AVL *avl)
   *  acao:        funcao que retorna o fator de balanço da árvore AVL
   *  entrada:     ponteiro para uma árvore AVL
   *  saida:       fator de balanço da árvore AVL
   *  suposicoes:  nenhuma
*/
int fatorBalanco(AVL *avl);

/* funcao: AVL *insereAVL(AVL *avl,void *info, int(*comp)(void *, void *))
   *  acao:        insere um novo nó na árvore AVL
   *  entrada:     ponteiro para a árvore avl (avl), um ponteiro para o elemento de informação a ser inserido (inf)
                e um função de callback para comparar a chave da árvore (comp)
   *  saida:		1, caso a inserção ocorra com sucesso
   					0, caso contrario
   *  suposicoes:  árvore avl
*/
AVL *insereAVL(AVL *avl, void *info, int(*comp)(void *, void *));

/* funcao: AVL *menorValor(AVL *avl)
   *  acao:        retorna o menor elemento da árvore AVL
   *  entrada:     ponteiro para a árvore avl (avl)
   *  saida:	    ponteiro para o menor elemento da árvore
   *  suposicoes:  árvore avl
*/
AVL *menorValor(AVL *avl);

/* funcao: AVL *deletaAVL(AVL *avl,void *info, int(*comp)(void *, void *))
   *  acao:        insere um novo nó na árvore AVL
   *  entrada:     ponteiro para a árvore avl (avl), um ponteiro para o elemento de informação a ser inserido (inf)
                e um função de callback para comparar a chave da árvore (comp)
   *  saida:		1, caso a inserção ocorra com sucesso
   					0, caso contrario
   *  suposicoes:  árvore avl
*/
AVL *deletaAVL(AVL *avl, void *info, int(*comp)(void *, void *));

/* funcao: void printPreOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informação considerando o caminho em pré-ordem da árvore AVL
   *  entrada:     ponteiro para a árvore avl e uma função de callback para imprimir o conteúdo
   *  saida:       void
   *  suposicoes:  árvore avl
*/
void printPreOrdem(AVL *avl, void(*imprime)(AVL *));

/* funcao: void printEmOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informação considerando o caminho em ordem da árvore AVL
   *  entrada:     ponteiro para a árvore avl e uma função de callback para imprimir o conteúdo
   *  saida:       void
   *  suposicoes:  árvore avl
*/
void printEmOrdem(AVL *avl, void(*imprime)(AVL *));

/* funcao: void printPosOrdem(AVL *avl, void(*imprime)(AVL *))
   *  acao:        imprime os elementos de informação considerando o caminho pós-ordem da árvore AVL
   *  entrada:     ponteiro para a árvore avl e uma função de callback para imprimir o conteúdo
   *  saida:       void
   *  suposicoes:  árvore avl
*/
void printPosOrdem(AVL *avl, void(*imprime)(AVL *));

#endif // __AVL_H__
