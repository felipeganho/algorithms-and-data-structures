#ifndef PQUEUEH
#define PQUEUEH

#define MAXPRIOR 10
// Definição da Estrutura de Dados FILA

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

// Definição das assinaturas das funções sobre o TAD FILA

//1) Inicialização e Liberação de uma Fila

// 1.a) função que aloca memória para uma Fila, inicializando seus campos
//		Entrada: void
//		Saída: ponteiro para uma lista
PQueue *createPQueue();

// 1.b) função que aloca memória para um no, inicializando seus campos
//		Entrada: void
//		Saída: ponteiro para uma Node
Node *createNode();

//1.d) função que libera todo o espaço de memória usado por uma Fila
//		Entrada: ponteiro para uma fila
//		Saída: void
void freePQueue(PQueue *pqueue);

//2) Informações sobre Fila

// 2.a) Função que verifica se uma Fila é vazia
//		Entrada: ponteiro para uma Fila
//		Saída: bool (TRUE se a Fila é vazia, FALSE caso contrário
bool isEmptyPQueue(PQueue * pqueue);

// 2.b) Função que Imprime o conteudo da Fila
//		Entrada: ponteiro para uma fila
//		Saída: bool (TRUE se a fila é vazia, FALSE caso contrário
void printPQueue(PQueue *pqueue);

// 2.c) Função que verifica o tamanho da Fila
//		Entrada: ponteiro para uma fila
//		Saída: inteiro >=0 representando o tamanho da fila, -1 caso a fila seja nula
int lengthPQueue(PQueue *pqueue);

//3) Operações sobre Fila

// 3.c) Função que insere um elemento da fila (na última posição)
//		Entrada: ponteiro para uma fila
//		Saída: bool (TRUE se o elemento foi inserido, FALSE caso contrário
bool insertPQueue(PQueue *pqueue, int prior,int inf);

// 3.c) Função que retira um elemento da fila (da primeira posição)
//		Entrada: ponteiro para uma fila
//		Saída: ponteiro para Info com o elemento retirado
Node *getNextPriority(PQueue *pqueue,int prior);
Node *getPriviousPriority(PQueue *pqueue,int prior);


Node *removePQueue(PQueue *pqueue, int prior, int size);
void changePriorityPQueue(PQueue *pqueue,int sourcePrior,int destPrior);

int isFirstBeforeOrAfter(PQueue *pqueue,int sourcePrior,int destPrior);
//int isFirstAfter(PQueue *pqueue,int sourcePrior,int destPrior);


#endif // PQUEUEH
