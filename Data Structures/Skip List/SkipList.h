#ifndef __STACK_H__
#define __STACK_H__

#define MAXNIVEIS 5

/* defini��o da estrutura SkipList */
typedef struct no{
    int value;
    struct no *next[MAXNIVEIS];
}Node;

typedef struct{
    Node *niveis[MAXNIVEIS];
}Apontador;

typedef struct{
    Node *first;
}SkipList;

/*  cria tanto a cabe�a quanto os n�ves da estrutura
    Entrada: void
    Sa�da: ponteiro para um SkipList */
SkipList *createAll();

/*  cria a cabe�a da estrutura
    Entrada: void
    Sa�da: ponteiro para um SkipList */
SkipList *createHead();

/*  cria os n�ves da estrutura
    Entrada: ponteiro para um SkipList
    Sa�da: void */
void createList(SkipList *skpLst);

/*  cria os n�ves da estrutura Apontador
    Entrada: void
    Sa�da: ponteiro para um Apontador */
Apontador *createApont();

/*  cria um novo n�
    Entrada: inteiro value
    Sa�da: ponteiro para um Apontador */
Node *createNode(int value);

/*  verifica se a estrutura SkipList � vazia
    Entrada: ponteiro para um SkipList
    Sa�da: retorna um inteiro */
int isEmptyList(SkipList *skpLst);

/*  verifica se j� existe o elemento buscado na estrutrua SkipList
    Entrada: inteiro value, ponteiro para um SkipList, ponteiro para um Apontador e um inteiro imprimir
    Sa�da: retorna um inteiro */
int searchList(int value,SkipList *skpLst,Apontador *ListaH,int imprimir);

/*  insere um novo n� na estrutura SkipList
    Entrada: inteiro value, inteiro hierarquia e ponteiro para um SkipList
    Sa�da: retorna um inteiro */
int Insere(int value,int h,SkipList *skpLst);

/*  remove um elemento da estrutura SkipList
    Entrada: inteiro value e um ponteiro para um SkipList
    Sa�da: retorna um inteiro */
int removeList(int value,SkipList *skpLst);

/*  imprime todos os elementos de um n�vel passado como par�metro
    Entrada: ponteiro para um SkipList e um inteiro para hierarquia
    Sa�da: void */
void printListH(SkipList *skpLst, int h);

/*  imprime toda a estrutura SkipList
    Entrada: ponteiro para um SkipList
    Sa�da: void */
void printList(SkipList *skpLst);

/*  fun��o auxiliar para gravar no arquivo de sa�da true ou false
    Entrada: um vetor de char
    Sa�da: void */
void gravaSaidaStr(char nome[100]);

/*  fun��o auxiliar para gravar no arquivo de sa�da a chave
    Entrada: um inteiro
    Sa�da: void */
void gravaSaidaInt(int num);

/*  fun��o auxiliar para gravar tanto a chave quanto o n�vel
    Entrada: um inteiro para a chave e outro para o n�vel
    Sa�da: void */
void gravaSaidaPrint(int num,int nivel);

#endif // __STACK_H__
