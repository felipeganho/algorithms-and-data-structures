#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *v, int tamanho){
    int i, j, chave;

    v = (int *) malloc(tamanho * sizeof(int));

    for(i=0; i < tamanho; i++){
        printf("Entre com o valor para a posicao %d do vetor: ", i+1);
        scanf("%d", &v[i]);
    }

    for(i=1; i < tamanho; i++){
        chave = v[i];
        j = i - 1;
        while(j >= 0 && v[j] > chave){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
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

    insertionSort(v, t);

    return 1;
}
