#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *v, int tamanho){
    int i, j, t;

    v = (int *) malloc(tamanho * sizeof(int));

    for(i=0; i < tamanho; i++){
        printf("Entre com o valor para a posicao %d do vetor: ", i+1);
        scanf("%d", &v[i]);
    }

    for(i=0; i < tamanho; i++){
        for(j=1; j < tamanho; j++){
            if(v[j-1] > v[j]){
                t = v[j-1];
                v[j-1] = v[j];
                v[j] = t;
            }
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

    bubbleSort(v, t);

    return 1;
}

