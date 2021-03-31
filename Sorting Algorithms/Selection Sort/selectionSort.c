#include <stdio.h>
#include <stdlib.h>

void selectionSort(int *v, int tamanho){
    int i, j, min, troca;

    v = (int *) malloc(tamanho * sizeof(int));

    for(i=0; i < tamanho; i++){
        printf("Entre com o valor para a posicao %d do vetor: ", i+1);
        scanf("%d", &v[i]);
    }

    for(i=0; i < tamanho-1; i++){
        min = i;
        for(j=i+1; j < tamanho; j++){
            if(v[j] < v[min]){
                min = j;
            }
        }

        if(min != i){
            troca = v[min];
            v[min] = v[i];
            v[i] = troca;
        }
    }

    printf("\n");
    printf("********* VETOR ORDENADO *********\n");
    for(i=0; i< tamanho; i++){
        printf("%d\n", v[i]);
    }
}

int main() {
    int t, *v;

    printf("Entre com o tamanho do vetor: ");
    scanf("%d", &t);

    printf("\n");

    selectionSort(v, t);

    return 1;
}
