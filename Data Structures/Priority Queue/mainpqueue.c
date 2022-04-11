#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pqueue.cpp"

int main(void){

	PQueue *pqueue=createPQueue();
	//Node *ptr,*aux;

	insertPQueue(pqueue,0,1);
	insertPQueue(pqueue,0,2);
	insertPQueue(pqueue,0,3);
	insertPQueue(pqueue,1,4);
	insertPQueue(pqueue,2,5);
	insertPQueue(pqueue,2,6);
	insertPQueue(pqueue,5,7);
	insertPQueue(pqueue,7,8);
	insertPQueue(pqueue,7,9);
	insertPQueue(pqueue,9,10);
	insertPQueue(pqueue,0,11);
	insertPQueue(pqueue,3,12);
	insertPQueue(pqueue,2,13);
	insertPQueue(pqueue,5,14);
   	
   	printf("Original Queue: ");
	printPQueue(pqueue);
	printf("\nLinear Queue: ");
	printLinearPQ(pqueue);
/*	ptr=removePQueue(pqueue,2,1);
	aux=ptr;
	printf("SUB Queue: [ ");
	while(aux)
	{
		printf("%d ",aux->value);
		aux=aux->next;
	}
	printf(" ] ");	
	ptr=removePQueue(pqueue,0,12);
	aux=ptr;
	printf("SUB Queue: [ ");
	while(aux)
	{
		printf("%d ",aux->value);
		aux=aux->next;
	}
	printf(" ] ");	
		
	printf("Original Queue: ");
	printPQueue(pqueue);
	printf("\nLinear Queue: ");
	printLinearPQ(pqueue);*/
	changePriorityPQueue(pqueue,2,4);
	printf("Original Queue Priority change:: ");
	printPQueue(pqueue);
	printf("\nLinear Queue Priority change:: ");
	printLinearPQ(pqueue);
	
    getchar();
   return 0;
}

