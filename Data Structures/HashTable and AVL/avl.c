#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avlno
{
	char *info;
	int balance;
	struct avlno *left, *right;
}AVL;

AVL *createAVL(void)
{
    return NULL;
}

AVL *createNodeAVL(char inf[])
{
    AVL *ptr;
    if((ptr=(AVL *)malloc(sizeof(AVL)))){
        ptr->info=(char *)malloc(sizeof(strlen(inf)+1));
        strcpy(ptr->info,inf);
        ptr->balance=0;
        ptr->left=NULL;
        ptr->right=NULL;
        return ptr;
    }
    return NULL;
}

char *rootAVL(AVL *avl)
{
    if(!avl)return NULL;
    return avl->info;
}

//retorna a sub-árvore esquerda de uma árvore AVL
AVL *leftAVL(AVL *avl)
{
    if(!avl)return NULL;
    return avl->left;
}

//retorna a sub-árvore direita de uma árvore AVL
AVL *rightAVL(AVL *avl)
{
    if(!avl)return NULL;
    return avl->right;
}

AVL *searchAVL(AVL *avl,char inf[])
{
    if(!inf || !avl ) return NULL;
    if(strcmp(avl->info,inf)==0) return avl;
    else if(strcmp((rootAVL(avl)),inf) > 0 ) return searchAVL(leftAVL(avl),inf);
    else return searchAVL(rightAVL(avl),inf);
}

void LL_RotationAVL(AVL** avl)
{
	printf("\nLL_RotationAVL:1");
	AVL* b = *avl;
	AVL* a = b->left;
	b->left = a->right;
	a->right = b;
	a->balance = 0;
	b->balance = 0;
	*avl = a;
}

void RR_RotationAVL(AVL** avl)
{
	printf("\nRR_RotationAVL:1");
	AVL* a = *avl;
	AVL* b = a->right;
	a->right = b->left;
	b->left = a;
	a->balance = 0;
	b->balance = 0;
	*avl = b;
}

void LR_RotationAVL(AVL** avl)
{
	printf("\nLR_RotationAVL:1");
	AVL *c = *avl;
	AVL *a = c->left;
	AVL *b = a->right;

	c->left = b->right;
	a->right = b->left;
	b->left = a;
	b->right = c;
	switch(b->balance)
	{
	  case -1:
		a->balance = 0;
		c->balance = 1;
		break;
	  case 0:
		a->balance = 0;
		c->balance = 0;
		break;
	  case +1:
		a->balance = -1;
		c->balance = 0;
		break;
	}
	b->balance = 0;
	*avl = b;
}

void RL_RotationAVL(AVL** avl)
{
	printf("\nRL_RotationAVL:1");
	AVL *a = *avl;
	AVL *c = a->right;
	AVL *b = c->left;

	c->left = b->right;
	a->right = b->left;
	b->left = a;
	b->right = c;
	switch(b->balance)
	{
		case -1:
		a->balance = 0;
		c->balance = 1;
		break;
		case 0:
		a->balance = 0;
		c->balance = 0;
		break;
		case +1:
		a->balance = -1;
		c->balance = 0;
		break;
	}
	b->balance = 0;
	*avl = b;
}

//growup indica que apos a insercao a avl cresceu
int auxInsertAVL(AVL** avl, char inf[], int *growup)
{
	if (*avl==NULL)
	{
		printf("\nauxInsertAVL:1");
    	*avl=createNodeAVL(inf);
    	*growup=1;
		return 1;
	}

	//se o nó já existe, o mesmo não será inserido
    if(strcmp((*avl)->info,inf)==0){
        printf("ENTROU AQUI");
        printf("\n%s\n",(*avl)->info);
        printf("%s",inf);
        return 0;
    }

	// insercao na sub-arvore esquerda
	if(strcmp((*avl)->info,inf) > 0)
	{
		printf("\nauxInsertAVL:2");
    	if (auxInsertAVL(&(*avl)->left,inf,growup))
		{
		    if (*growup)
			{
				switch ((*avl)->balance)
				{
					case 1:
						if ((leftAVL(*avl))->balance == 1)
					    	LL_RotationAVL(avl);
					 	else
							LR_RotationAVL(avl);
						*growup = 0;
						break;
					case 0:
						(*avl)->balance=1;
						*growup = 1;
						break;
					case -1:
						(*avl)->balance = 0;
						*growup= 0;
						break;
				}
			}
			return 1;
		}
		else return 0;
	}

	// insercao na sub-arvore direita
  	if(strcmp((*avl)->info,inf) < 0)
	{
		if(	auxInsertAVL(&(*avl)->right,inf,growup))
		{
			printf("\nauxInsertAVL:3");
			if(*growup)
			{
				switch ((*avl)->balance)
				{
					case -1:
						if ((rightAVL(*avl))->balance == -1)
							RR_RotationAVL(avl);
						else
							RL_RotationAVL(avl);
						*growup = 0;
						break;
					case 1:
						(*avl)->balance = 0;
						*growup = 0;
						break;
					case 0:
						(*avl)->balance = -1;
						*growup = 1;
						break;
				}
			}
			return 1;
		}
		else return 0;
	}
	//printf("ASFASFAFASFASF");
	return 0;
}

//função que insere um elemento na árvore AVL
int insertAVL(AVL **avl,char inf[])
{
	int growup=0;
	return auxInsertAVL(avl,inf,&growup);
}

//função que retorna o maior elemento da AVL
AVL *findLargestElementAVL(AVL *avl){
    if(!avl || !rightAVL(avl))return avl;
    else return findLargestElementAVL(rightAVL(avl));
}

//função auxiliar para a função delete
AVL *auxDeleteAVL(AVL *avl, char inf[], int *growup){
    AVL *aux;
    int bal;

    if(!inf || !avl){
        printf("\nImpossivel Remover elemento");
        return avl;
    }

    if(strcmp(avl->info,inf) > 0){
        avl->left=auxDeleteAVL(avl->left,inf,growup);

        if(*growup){
            switch(avl->balance){
                case +1:
                    avl->balance=0;
                    break;
                case 0:
                    avl->balance=-1;
                    growup=0;
                    break;
                case -1:
                    aux=avl->right;
                    bal=aux->balance;
                    if(bal<=0) RR_RotationAVL(&avl);
                    else RL_RotationAVL(&avl);
            }
        }
    }

    else{
        if(strcmp(avl->info,inf) < 0){
            avl->right=auxDeleteAVL(avl->right,inf,growup);

            if(*growup){
                switch(avl->balance){
                    case -1:
                        avl->balance=0;
                        break;

                    case 0:
                        avl->balance=+1;
                        *growup=0;
                        break;

                    case +1:
                        aux=avl->left;
                        bal=aux->balance;
                        if(bal>=0) LL_RotationAVL(&avl);
                        else LR_RotationAVL(&avl);
                }
            }
        }
        else{

            if(avl->right==NULL){
                AVL *q=avl;
                avl=q->left;
                *growup=1;
                free(q->info);
                free(q);
            }
            else{
                if(avl->left==NULL){
                    AVL *q=avl;
                    avl=q->right;
                    *growup=1;
                    free(q->info);
                    free(q);
                }
                else{
                    struct avlno *aux=findLargestElementAVL(leftAVL(avl));
                    strcpy(avl->info,aux->info);
                    char *inf;
                    strcpy(inf,aux->info);
                    //q=NULL;
                    avl->left=auxDeleteAVL(leftAVL(avl),inf,growup);

                    if(*growup)
                        switch(avl->balance){
                            case -1:
                                avl->balance=0;
                                break;

                            case 0:
                                avl->balance=+1;
                                *growup=0;
                                break;

                            case +1:
                                aux=avl->left;
                                bal=aux->balance;
                                if(bal>=0) LL_RotationAVL(&avl);
                                else LR_RotationAVL(&avl);
                        }
                }
            }
        }
    }
    return avl;
}

//função que deleta um nó da árvore AVL
AVL *deleteAVL(AVL *avl, char inf[]){
    int growup=0;
    return auxDeleteAVL(avl,inf,&growup);
}

//função auxiliar para imprimir a árvore AVL
void auxprintAVL(AVL *avl)
{
	if(!avl) return;
    auxprintAVL(leftAVL(avl));
    printf(" [%s]", (rootAVL(avl)));
    auxprintAVL(rightAVL(avl));
}

//função que imprime a árvore AVL
void printAVL(AVL *avl)
{

	if(!avl) return;
	auxprintAVL(leftAVL(avl));
    printf(" [%s]", (rootAVL(avl)));
    auxprintAVL(rightAVL(avl));

}

//função que imprime os elementos no percurso pré-ordem
void printPreOrderAVL(AVL *avl)
{
	if(!avl) return;
	printf(" [%s]", (rootAVL(avl)));
	printPreOrderAVL(leftAVL(avl));
    printPreOrderAVL(rightAVL(avl));
}

//int main(){
//    char nome[20]="felipe";
//    AVL *avl=createAVL();
//    insertAVL(&avl,nome);
//    insertAVL(&avl,nome);
//    return 21;
//}
