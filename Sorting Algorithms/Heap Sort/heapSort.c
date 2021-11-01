#include <stdio.h>
#include <stdlib.h>

//retorna o indice do pai
int pai(int indice) {
    return (indice-1)/2;
}

//retorna o filho da esquerda
int esquerda(int indice){
    return 2 * indice + 1;
}

//retorna o filho da direita
int direita(int indice){
    return 2 * indice + 2;
}

//heap máximo
void maxHeapify(int *v, int tamanho, int indice){
    int maior=indice, l=0, r=0, aux=0;

    l = esquerda(indice);
    r = direita(indice);

    if (l < tamanho && v[l] > v[maior]) maior= l;

    if (r < tamanho && v[r] > v[maior]) maior= r;

    if (maior!= indice){
        aux = v[indice];
        v[indice]= v[maior];
        v[maior] = aux;
        maxHeapify(v, tamanho, maior);
    }
}

void constroiHeapMax(int *v, int tamanho){
    for (int i = (tamanho / 2) - 1; i >= 0; i--)
        maxHeapify(v, tamanho, i);
}

void heapSort(int *v, int tamanho){
    int aux;

    constroiHeapMax(v, tamanho);
    for (int i=tamanho-1; i>=0; i--){
        aux = v[0];
        v[0]= v[i];
        v[i] = aux;
        maxHeapify(v, i, 0);
    }
}

//retorna o elemento de prioridade máxima
int retiraMaximo(int *v, int tamanho){
    int maior=v[0];

    if(tamanho < 1) return 0;

    v[0] = v[tamanho-1];
    maxHeapify(v, --tamanho, 0);

    return maior;
}

//aumenta valor da chave e mantém heap máximo
void incrementaChave(int *v, int indice, int chave){
    int aux=0;

    if(chave < v[indice]) return;   //nova chave menor que atual

    v[indice] = chave;
    while(indice>0 && v[pai(indice)] < v[indice]){
        aux = v[indice];
        v[indice] = v[pai(indice)];
        v[pai(indice)] = aux;
        indice = pai(indice);
    }
}

//insere um elemento mantendo o heap máximo
void insereHeapMaximo(int *v, int chave, int tamanho){
    tamanho++;
    v[tamanho] = -1;
    incrementaChave(v, tamanho, chave);
}

int main(){
//    int t=0, *v;

//    printf("Entre com o tamanho do vetor: ");
//    scanf("%d", &t);

//    v = (int *)malloc(t * sizeof(int));


//    for(int i=0; i < t; i++){
//        printf("Entre com o valor para a posicao %d do vetor: ", i);
//        scanf("%d", &v[i]);
//    }

    int vet[6] = { 12,6,10,5,1,9  };
    int *v = vet;

//    heapSort(v, 6);

//    maxHeapify(v, 9, 0);

    for(int i=0; i < 6; i++) printf("%d ", v[i]);
    printf("\n");

    int maior = retiraMaximo(v, 6);

    printf("Retira maximo: %d \n", maior);
//
//    for(int i=0; i < 8; i++) printf("%d ", v[i]);
//    printf("\n");
//
//    incrementaChave(v, 2, 49);
//
//    for(int i=0; i < 8; i++) printf("%d ", v[i]);
//    printf("\n");

//    insereHeapMaximo(v, 32, 8);

    for(int i=0; i < 5; i++) printf("%d ", v[i]);
    printf("\n");

    return 1;
}
