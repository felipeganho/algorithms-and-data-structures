#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

//definição da estrutura de hashtable
typedef struct tnode{
    char *info;
    struct tnode *proximo;
}Node;

//cria hashtable
void createHT(Node *hashtable[],int sizeht);

//cria no
Node *createNodeHT(char *inf);

//função hash
int functionHT(char *inf,int sizeht);

//insere na tabela hash
void insertHT(Node *hashtable[],int sizeht,char *word);

//deleta da tabela hash
void deleteHT(Node *hashtable[],int sizeht,char *word);

//busca na tabela hash
Node *searchHT(Node *hashtable[],int sizeht,char *word);

//encontra o meio
Node *mEio(Node *hashtable[],int ini,int fim,int sizeht,char *word);

//imprime a tabela hash
void printHT(Node *hashtable[],int sizeht);

#endif // __HASHTABLE_H__
