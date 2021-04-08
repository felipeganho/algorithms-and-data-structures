#include "ListaGen.c"

void imprime_int(void *v){
    int *a = (int *)v;
    printf("%d ", *a);
}

int main(){
    int *id = NULL;
    int op;
    ListaGen *L = NULL;

    do {
        printf("Menu:\n 1. Inserir um inteiro\n 2. Imprimir a lista\n 0. Sair\n Escolha a opcao: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                id = (int *)malloc(sizeof(int));
                if(!id) return 0;
                printf("Digite um numero: ");
                scanf("%d", id);
                L = insere_listagen(L, id);
                break;

            case 2:
                percorre_listagen(L, imprime_int);
                printf("\n");
                break;

            case 0:
                printf("Fim do programa. \n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while(op!=0);

    return 0;
}
