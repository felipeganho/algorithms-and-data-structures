#include<stdio.h>
#include<stdlib.h>

void merge(int *v, int *L, int l, int *R, int r) {
	int i=0, j=0, k=0;

	while(i < l && j < r) {
		if(L[i] < R[j]) v[k++] = L[i++];
		else v[k++] = R[j++];
	}
	while(i < l) v[k++] = L[i++];
	while(j < r) v[k++] = R[j++];
}

void mergeSort(int *v, int n) {
	int m, i, *L, *R;

	if(n < 2) return;

	m = n/2;

	L = (int*)malloc(m * sizeof(int));
	R = (int*)malloc((n - m) * sizeof(int));

	for(i=0; i < m; i++) L[i] = v[i];
	for(i=m; i < n; i++) R[i-m] = v[i];

	mergeSort(L, m);
	mergeSort(R, n-m);
	merge(v, L, m, R, n-m);
    free(L);
    free(R);
}

int main() {

	int t, *v;

    printf("Entre com o tamanho do vetor: ");
    scanf("%d", &t);

    v = (int *)malloc(t * sizeof(int));

    for(int i=0; i < t; i++){
        printf("Entre com o valor para a posicao %d do vetor: ", i+1);
        scanf("%d", &v[i]);
    }

    printf("\n");

    mergeSort(v, t);

    for(int i=0; i < t; i++) printf("%d ", v[i]);

    free(v);

    return 1;
}
