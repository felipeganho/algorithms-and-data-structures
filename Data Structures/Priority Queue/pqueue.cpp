#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pqueue.h"

//1) Inicialização e Liberação de uma Fila

// 1.a) função que aloca memória para uma Fila, inicializando seus campos
//		Entrada: voidd
//		Saída: ponteiro para uma lista
PQueue *createPQueue()
{
    PQueue *ptr;
    int i;
    ptr=(PQueue *)malloc(sizeof(PQueue));
    if(ptr)
	{
        ptr->sizePQ=0;
        for(i=0; i< MAXPRIOR;i++){
        	ptr->queues[i].first=NULL;
        	ptr->queues[i].sizeQ=0;
		} 
        return ptr;
    }
    return NULL;
}

// 1.b) função que aloca memória para um no, inicializando seus campos
//		Entrada: void
//		Saída: ponteiro para uma Node
Node *createNode(int inf)
{
    Node *ptr;
    ptr=(Node *)malloc(sizeof(Node));
    if(ptr){
        ptr->value=inf;
        ptr->next=NULL;
        return ptr;
    }
    return NULL;
}


//1.d) função que libera todo o espaço de memória usado por uma Fila
//		Entrada: ponteiro para uma fila
//		Saída: void

void freeQueue(PQueue *pqueue)
{
    Node *ptr, *aux;
    if (!pqueue) return;
    ptr=pqueue->queues[0].first;
    while(ptr)
    {
        aux=ptr->next;
        free(ptr);
        ptr=aux;
    }
    free(pqueue);
}

//2) Informações sobre Fila

// 2.a) Função que verifica se uma Fila é vazia
//		Entrada: ponteiro para uma Fila
//		Saída: bool (TRUE se a Fila é vazia, FALSE caso contrário

bool isEmptyPQueue(PQueue * pqueue)
{
    return (!pqueue || pqueue->sizePQ==0);
}

// 2.b) Função que Imprime o conteudo da Fila
//		Entrada: ponteiro para uma fila
//		Saída: bool (TRUE se a fila é vazia, FALSE caso contrário
void printPQueue(PQueue *pqueue) {

    Node *ptr;
	int i,j;
    if(isEmptyPQueue(pqueue)) return;
    for(i=0;i<MAXPRIOR;i++)
    {
		printf("\nPRIORIDADE %d =", i);
		printf("\n[ ");
		if(pqueue->queues[i].sizeQ==0) printf(" SEM ELEMENTOS ");
		else
		{
			ptr=pqueue->queues[i].first;
			for(j=0;j<pqueue->queues[i].sizeQ;j++,ptr=ptr->next) printf("(%d) ",ptr->value);
		}
		printf(" ]");
	}
}
void printLinearPQ(PQueue *pqueue)
{
	Node *ptr;
	int i;
    if(isEmptyPQueue(pqueue)) return;
    for(i=0;i<MAXPRIOR && pqueue->queues[i].first==NULL;i++)
    {    printf("\n%d ",i);}
    if(pqueue->queues[i].first!=NULL)
    {
		printf("\n[ ");
		ptr=pqueue->queues[i].first;
		for(;ptr;ptr=ptr->next) printf("(%d) ",ptr->value);
		printf(" ]");
	}
}

// 2.c) Função que verifica o tamanho da Fila
//		Entrada: ponteiro para uma fila
//		Saída: inteiro >=0 representando o tamanho da fila, -1 caso a fila seja nula
int lengthPQueue(PQueue *pqueue)
{
	if (!pqueue) return -1;
	return pqueue->sizePQ;
}

//3) Operações sobre Fila

// 3.c) Função que insere um elemento da fila (na última posição)
//		Entrada: ponteiro para uma fila
//		Saída: bool (TRUE se o elemento foi inserido, FALSE caso contrário
bool insertPQueue(PQueue *pqueue, int prior,int inf)
{
    Node *ptr,*pptr,*nptr;
    int i;
    if(prior<0 || prior>=MAXPRIOR) return false;
    if(!pqueue || !(ptr=createNode(inf))) return false;
    if(pqueue->queues[prior].sizeQ==0)
    {
		pptr=getPriviousPriority(pqueue,prior);
		nptr=getNextPriority(pqueue,prior);
		if(pptr)pptr->next=ptr;
		ptr->next=nptr;
		pqueue->queues[prior].first=ptr;
		
	}
	else
	{
		nptr=pqueue->queues[prior].first;
		for(i=1;i<pqueue->queues[prior].sizeQ;i++,nptr=nptr->next);
		ptr->next=nptr->next;
		nptr->next=ptr;
	}
	pqueue->sizePQ++;
	pqueue->queues[prior].sizeQ++;
	return true;
}

Node *getNextPriority(PQueue *pqueue,int prior)
{
	int i=prior+1;
	while(i<MAXPRIOR && pqueue->queues[i].first==NULL)i++;
	if (i>=MAXPRIOR)return NULL;
	return pqueue->queues[i].first;
	
}

Node *getPriviousPriority(PQueue *pqueue,int prior)
{
	Node *ptr=NULL;
	int i=prior-1,j;
	while(i>0 && pqueue->queues[i].first==NULL)
	{
		i--;
	}
	if (i<0)return NULL;
	ptr=pqueue->queues[i].first;
	for(j=1;j<(pqueue->queues[i].sizeQ);j++,ptr=ptr->next);
	return ptr;
}

// 3.c) Função que retira um elemento da fila (da primeira posição)
//		Entrada: ponteiro para uma fila
//		Saída: ponteiro para Info com o elemento retirado
Node *removePQueue(PQueue *pqueue, int prior, int size) 
{
    Node *ptr,*lptr,*pptr;
    int i;
    
    if(prior<0 || prior>=MAXPRIOR || pqueue->queues[prior].first==NULL || size<=0) return NULL;
    ptr=pqueue->queues[prior].first;
    pptr=getPriviousPriority(pqueue,prior);
    printf("\nremovePQueue: 1");
    for(lptr=ptr,i=1; (i<size) && (i<pqueue->queues[prior].sizeQ) ; i++,lptr=lptr->next){}
    printf("\nremovePQueue: 2");
   	if(pptr!=NULL)
   	{
		pptr->next=lptr->next;
	}
   	if(size>=pqueue->queues[prior].sizeQ)
   	{
		pqueue->queues[prior].first=NULL;
	}
   	else
   		pqueue->queues[prior].first=lptr->next;
	lptr->next=NULL;
	pqueue->sizePQ-=size;
	pqueue->queues[prior].sizeQ-=size;
	return lptr;
}

/* funcao: void changePriorityPQueue(Pqueue *pqueue,int source,int dest)
   *  acao:        altera a prioridade de todos os elementos de uma fila de origem, colocando todos os seus elementos
   					no final de uma fila de destino. A função é implementada apenas com reapontamentos
   *  entrada:     ponteiro para uma fila de prioridades (pqueue), a prioridade de onde serão retirados os elementos (sourcePrior) e
   					a prioridade onde serão colocados os elementos (destPrior)
   *  saida:       void
   *  suposicoes:  nenhuma
*/
void changePriorityPQueue(PQueue *pqueue,int sourcePrior,int destPrior)
{
	Node *psptr, *nsptr,*pdptr, *ndptr, *ptr;
	int i;
	
	if(sourcePrior<0 || sourcePrior>=MAXPRIOR || destPrior<0 || destPrior>=MAXPRIOR || sourcePrior==destPrior || pqueue==NULL || pqueue->queues[sourcePrior].first==NULL) return;
	psptr=getPriviousPriority(pqueue,sourcePrior);
	nsptr=getNextPriority(pqueue,sourcePrior);
	pdptr=getPriviousPriority(pqueue,destPrior);
	ndptr=getNextPriority(pqueue,destPrior);
	if(psptr)printf("\nchangePriorityPQueue: psptr %d",psptr->value);
	if(nsptr)printf("\nchangePriorityPQueue: nsptr %d",nsptr->value);
	if(pdptr)printf("\nchangePriorityPQueue: pdptr %d",pdptr->value);
	if(ndptr)printf("\nchangePriorityPQueue: ndptr %d",ndptr->value);
	
	
	printf("changePriorityPQueue: 1");
	if(pqueue->queues[destPrior].first)
	{
		printf("changePriorityPQueue: 2");
		getchar();
		ptr=pqueue->queues[destPrior].first;
		for(i=1;i<pqueue->queues[destPrior].sizeQ;i++,ptr=ptr->next)
		ptr->next=pqueue->queues[sourcePrior].first;
		ptr=ptr->next;
		for(i=1;i<pqueue->queues[sourcePrior].sizeQ;i++,ptr=ptr->next)
		ptr->next=ndptr;
		if(psptr)psptr=nsptr;
	}
	else
	{
		printf("changePriorityPQueue: 3 ");
		getchar();
			
		pqueue->queues[destPrior].first=pqueue->queues[sourcePrior].first;
		printf("\nchangePriorityPQueue: isFirstBefore= %d", isFirstBeforeOrAfter(pqueue,sourcePrior,destPrior));
	//	printf("\nchangePriorityPQueue: isFirstAfter= %d", isFirstAfter(pqueue,sourcePrior,destPrior));
		
		if( (isFirstBeforeOrAfter(pqueue,sourcePrior,destPrior))==0)
		{
			printf("changePriorityPQueue: 4... ");
			getchar();
			printf("changePriorityPQueue: 3 %d",pqueue->queues[destPrior].first->value);
			getchar();
			
			ptr=pqueue->queues[sourcePrior].first;
			for(i=1;i<pqueue->queues[sourcePrior].sizeQ;i++,ptr=ptr->next)
			ptr->next=ndptr;
			printf("changePriorityPQueue: 5 %d %d",ptr->value,ndptr->value);
			getchar();
			if(psptr)psptr=nsptr;
			if(pdptr)pdptr=pqueue->queues[sourcePrior].first;
			
		}
	}
	pqueue->queues[destPrior].sizeQ+=pqueue->queues[sourcePrior].sizeQ;
	pqueue->queues[sourcePrior].sizeQ=0;
	pqueue->queues[sourcePrior].first=NULL;
	printLinearPQ(pqueue);
	return;
}

int isFirstBeforeOrAfter(PQueue *pqueue,int sourcePrior,int destPrior)
{
	int i;
	if(sourcePrior<destPrior)
	{
		for(i=destPrior-1; i>=sourcePrior; i--)
		{
			if(pqueue->queues[i].first!=NULL)
			{
				if(i==sourcePrior) return 1;
				else return 0;
			}
		}
	}
	else
	{
		for(i=destPrior+1; i<=sourcePrior; i++)
		{
			if(pqueue->queues[i].first!=NULL)
			{
				if(i==sourcePrior)	return 1;
				else return 0;	
			}
		}
	}
	return 0;
 }
	


