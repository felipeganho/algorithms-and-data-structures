#ifndef __STACK_H__
#define __STACK_H__

#define MAXNIVEIS 5

/* definição da estrutura SkipList */
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

/*  cria tanto a cabeça quanto os níves da estrutura
    Entrada: void
    Saída: ponteiro para um SkipList */
SkipList *createAll();

/*  cria a cabeça da estrutura
    Entrada: void
    Saída: ponteiro para um SkipList */
SkipList *createHead();

/*  cria os níves da estrutura
    Entrada: ponteiro para um SkipList
    Saída: void */
void createList(SkipList *skpLst);

/*  cria os níves da estrutura Apontador
    Entrada: void
    Saída: ponteiro para um Apontador */
Apontador *createApont();

/*  cria um novo nó
    Entrada: inteiro value
    Saída: ponteiro para um Apontador */
Node *createNode(int value);

/*  verifica se a estrutura SkipList é vazia
    Entrada: ponteiro para um SkipList
    Saída: retorna um inteiro */
int isEmptyList(SkipList *skpLst);

/*  verifica se já existe o elemento buscado na estrutrua SkipList
    Entrada: inteiro value, ponteiro para um SkipList, ponteiro para um Apontador e um inteiro imprimir
    Saída: retorna um inteiro */
int searchList(int value,SkipList *skpLst,Apontador *ListaH,int imprimir);

/*  insere um novo nó na estrutura SkipList
    Entrada: inteiro value, inteiro hierarquia e ponteiro para um SkipList
    Saída: retorna um inteiro */
int Insere(int value,int h,SkipList *skpLst);

/*  remove um elemento da estrutura SkipList
    Entrada: inteiro value e um ponteiro para um SkipList
    Saída: retorna um inteiro */
int removeList(int value,SkipList *skpLst);

/*  imprime todos os elementos de um nível passado como parâmetro
    Entrada: ponteiro para um SkipList e um inteiro para hierarquia
    Saída: void */
void printListH(SkipList *skpLst, int h);

/*  imprime toda a estrutura SkipList
    Entrada: ponteiro para um SkipList
    Saída: void */
void printList(SkipList *skpLst);

/*  função auxiliar para gravar no arquivo de saída true ou false
    Entrada: um vetor de char
    Saída: void */
void gravaSaidaStr(char nome[100]);

/*  função auxiliar para gravar no arquivo de saída a chave
    Entrada: um inteiro
    Saída: void */
void gravaSaidaInt(int num);

/*  função auxiliar para gravar tanto a chave quanto o nível
    Entrada: um inteiro para a chave e outro para o nível
    Saída: void */
void gravaSaidaPrint(int num,int nivel);

#endif // __STACK_H__
