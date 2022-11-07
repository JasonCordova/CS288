#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(int *array, int length);
void print_array(int *array, int length);
void selection_sort(int *array, int length);
void mergeSort(int* array, int l, int r);
void merge(int* array, int l, int m, int r);

int main(){

	
	int length = 10;
	clock_t start, end;
	int *array = (int*)malloc(sizeof(int) * length);
	fill_array(array, length);
	start = clock();
	mergeSort(array, 0, length-1);
	end = clock() - start;
	double time_taken = ((double) end)/CLOCKS_PER_SEC;
	printf("Length: %d | Time: %f\n", length, time_taken);

}

void swap(int *xp, int *yp){

	int temp = *xp;
	*xp = *yp;
	*yp = temp;

}

void fill_array(int *array, int length){

	for (int i = 0; i < length; i++){

		array[i] = rand() % 100;

	}

}

void print_array(int* array, int length){

	for (int i = 0; i < length; i++){

		printf("%d ", array[i]);

	}

	printf("\n");

}

void mergeSort(int* array, int l, int r){

    if (l < r){

        int m = l + (r - 1) / 2;

        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);

    }

}

void selection_sort(int* array, int length){

	int i, j, min_idx;

	for (i = 0; i < length - 1; i++){

		min_idx = i;
		for (j = i+1; j < length; j++)
			if (array[j] < array[min_idx])
				min_idx = j;

				if (min_idx != i)
					swap(&array[min_idx], &array[i]);

	}

}
