/*
    Estudantes:
        Felipe Silva Ganho
        Leonardo Loureiro de Almeida
*/

#include <stdio.h>
#include <stdlib.h>
#include "avl.c"

//Estrutura utilizada para o cliente
typedef struct{
    int matricula;
    int cpf;
    float nota;
}Aluno;

//Cria um estrutura do tipo Aluno
Aluno *cria_aluno(int matricula, int cpf, float nota){
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    aluno->matricula = matricula;
    aluno->cpf = cpf;
    aluno->nota = nota;
    return aluno;
}

//Imprime o conteúdo da estrutura do tipo Aluno de cada árvore AVL
void imprime(AVL *avl){
    if(!avl) return;
    Aluno *aluno = (Aluno *)avl->info;
    printf("\nFator de Balanceamento: %d\nMatricula: %d\nCPF: %d\nNota: %.2f\n"
           , fatorBalanco(avl), aluno->matricula, aluno->cpf, aluno->nota);
}

//Imprime o fator de balanço e chave de cada árvore AVL
void imprimeAVL(AVL *avl){
    if(!avl) return;
    Aluno *aluno = (Aluno *)avl->info;
    printf("[FB:%d Ch:%d] ", fatorBalanco(avl), aluno->matricula);
}

//Função de callback utilizada para comparar a chave passada com a chave da árvore AVL
int compara(void *info1, void *info2){
    int *matriculaAVL = (int *)info1;
    int *matricula = (int *)info2;

    if((*matriculaAVL) == (*matricula)) return 0;
    else if((*matriculaAVL) > (*matricula)) return -1;
    else return 1;
}

int main(){
    AVL *avl=criaAVL();
    int op;
    int x, y;
    float z;
    int *matricula=NULL;

    //Menu para a aplicação - Inserção, Deleção, Impressão e Busca
    do{
        printf("\nMenu:\n 1. Inserir um Aluno\n 2. Deletar um elemento da Arvore\n 3. Buscar um elemento na Arvore\n 4. Imprimir a Arvore [Fator de Balanceamento e Chave]\n 5. Imprimir Todos Elementos da Arvore \n 0. Sair\n\n Escolha a opcao: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                printf("\nMatricula: ");
                scanf("%d",&x);
                printf("CPF:");
                scanf("%d",&y);
                printf("Nota:");
                scanf("%f",&z);
                Aluno *aluno = cria_aluno(x, y, z);
                avl=insereAVL(avl, aluno, &compara);
                printf("\nElemento Inserido: \n");
                imprime(buscaAVL(avl, aluno, &compara));
                break;

            case 2:
                printf("\nMatricula:");
                matricula = (int *)malloc(sizeof(int));
                scanf("%d",matricula);
                imprime(buscaAVL(avl, matricula, &compara));
                printf("\n");
                avl=deletaAVL(avl, matricula, &compara);
                break;

            case 3:
                printf("\nMatricula:");
                matricula = (int *)malloc(sizeof(int));
                scanf("%d",matricula);
                imprime(buscaAVL(avl, matricula, &compara));
                break;

            case 4:
                printEmOrdem(avl, &imprimeAVL);
                break;

            case 5:
                printEmOrdem(avl , &imprime);
                break;

            case 0:
                printf("Fim do programa. \n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(op!=0);

    return 1;
}
