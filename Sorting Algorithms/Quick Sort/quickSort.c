#include <stdio.h>
#include <stdlib.h>

int particao(int *v, int p, int r){
    int x=0, i=0, j=0, aux;

    x = v[r];
    i = p-1; 

    for(j=p; j < r; j++){
        if(v[j] <= x){
            printf("AQUI v[j] <= x\n");
            i++;    
            aux = v[i]; 
            v[i] = v[j];
            v[j] = aux;
            printf("v[i]: %d  v[j]: %d", v[i], v[j]);
        }
    }
    aux = v[i+1]; 
    v[i+1] = v[r]; 
    v[r] = aux; 

    return i+1;
}

void quickSort(int *v, int p, int r){
    int q=0;

    if(p < r){
        printf("AQUI p<r\n");
        q = particao(v, p, r);
        quickSort(v, p, q-1);
        quickSort(v, q+1, r);
    }
}

int main(){
    int t=0, *v;

    printf("Entre com o tamanho do vetor: ");
    scanf("%d", &t);

    v = (int *)malloc(t * sizeof(int));

    for(int i=0; i < t; i++){
        printf("Entre com o valor para a posicao %d do vetor: ", i+1);
        scanf("%d", &v[i]);
    }

    printf("\n");

    quickSort(v, 0, t-1);

    for(int i=0; i < t; i++) printf("%d ", v[i]);

    free(v);

//	int v[] = {6,2,3,1,9,10,15,13,12,17};

    return 1;
}
