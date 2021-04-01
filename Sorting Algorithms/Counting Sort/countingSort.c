/*
    Explanation about Counting Sort:
    Counting sort is a sorting algorithm that sorts the elements of an array
    by counting the number of occurrences of each unique element in the array.
    The count is stored in an auxiliary array and the sorting is done by mapping
    the count as an index of the auxiliary.

    Complexity: O(n+k)
*/

#include <stdio.h>
#include <stdlib.h>

void countingSort(int v[], int b[], int k, int size){
	int *c = (int *)malloc(k * sizeof(int));
	int i=0;

	for(i = 0; i < k; i++){
		c[i] = 0;
	}

	for(i = 0; i < size; i++){
		c[v[i]]++;
	}

	for(i = 1; i < k; i++){
		c[i] = c[i] + c[i-1];
	}

	for(i = 0; i <= size-1; i++){
		b[c[v[i]]] = v[i];
		c[v[i]]--;
	}
}

int main(){
	int a[] = {1,4,1,2,7,5,100};
	int size = sizeof(a)/sizeof(int);
	int *b = (int*)malloc(sizeof(int)*(size));

	for(int i = 1; i <= size; i++){
		b[i] = 0;
	}

	countingSort(a, b, 100, size);

	for(int i = 1; i <= size; i++){
		printf("%d ", b[i]);
	}

	return 1;
}
