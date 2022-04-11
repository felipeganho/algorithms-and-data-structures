#ifndef PQUEUEH
#define PQUEUEH

#define MAXPRIOR 10
// Defini��o da Estrutura de Dados FILA

typedef struct tnode
{
	struct tnode *next;
	int value;
}Node;
typedef struct
{
	int sizeQ;
	Node *first;
}Queue;
typedef struct
{
	int sizePQ;
	Queue queues[MAXPRIOR];
}PQueue;

// Defini��o das assinaturas das fun��es sobre o TAD FILA

//1) Inicializa��o e Libera��o de uma Fila

// 1.a) fun��o que aloca mem�ria para uma Fila, inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma lista
PQueue *createPQueue();

// 1.b) fun��o que aloca mem�ria para um no, inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma Node
Node *createNode();

//1.d) fun��o que libera todo o espa�o de mem�ria usado por uma Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: void
void freePQueue(PQueue *pqueue);

//2) Informa��es sobre Fila

// 2.a) Fun��o que verifica se uma Fila � vazia
//		Entrada: ponteiro para uma Fila
//		Sa�da: bool (TRUE se a Fila � vazia, FALSE caso contr�rio
bool isEmptyPQueue(PQueue * pqueue);

// 2.b) Fun��o que Imprime o conteudo da Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: bool (TRUE se a fila � vazia, FALSE caso contr�rio
void printPQueue(PQueue *pqueue);

// 2.c) Fun��o que verifica o tamanho da Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: inteiro >=0 representando o tamanho da fila, -1 caso a fila seja nula
int lengthPQueue(PQueue *pqueue);

//3) Opera��es sobre Fila

// 3.c) Fun��o que insere um elemento da fila (na �ltima posi��o)
//		Entrada: ponteiro para uma fila
//		Sa�da: bool (TRUE se o elemento foi inserido, FALSE caso contr�rio
bool insertPQueue(PQueue *pqueue, int prior,int inf);

// 3.c) Fun��o que retira um elemento da fila (da primeira posi��o)
//		Entrada: ponteiro para uma fila
//		Sa�da: ponteiro para Info com o elemento retirado
Node *getNextPriority(PQueue *pqueue,int prior);
Node *getPriviousPriority(PQueue *pqueue,int prior);


Node *removePQueue(PQueue *pqueue, int prior, int size);
void changePriorityPQueue(PQueue *pqueue,int sourcePrior,int destPrior);

int isFirstBeforeOrAfter(PQueue *pqueue,int sourcePrior,int destPrior);
//int isFirstAfter(PQueue *pqueue,int sourcePrior,int destPrior);


#endif // PQUEUEH
