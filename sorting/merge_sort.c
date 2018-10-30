// merge_sort
// https://github.com/ddamddi

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void MergeSort(int arr[], int left, int right);							 
void MergeTwoArea(int arr[], int left, int mid, int right);			
	
int main(int argc, char* argv[]){
	
	int i, N, Nlen;
	int K = 0, counter = 0;
	double Runtime;
	int * arr;
	int * arr_tmp;		// array for memcpy
	char str[30];		// string for fgets()
	FILE * fp;
	clock_t start_time;
	
	// check command line arguments.
	// Ex) <your_program> <N> <input_file> : argc = 3
	if(argc != 3){										
		puts("incorrect command line arguments.");		
		return -1;										
	}
	
	// Check N is integer or not, checking every single character in argv[1]
	// ex) aaa, 12a, a492 etc.
	Nlen = strlen(argv[1]);								
	for(i = 0; i< Nlen; i++){							
		if(argv[1][i] < '0' || argv[1][i] >'9'){		
			puts("N is not integer.");
			return -1;
		}
	}
	
	N = atoi(argv[1]);
	
	fp = fopen(argv[2],"rt");
	
	// check file open error.
	if(fp == NULL){			
		puts("file open fail.");
		return -1;
	}
	
	
	while(!feof(fp)){
		// count K (the number of integer in file)
		fgets(str, sizeof(str), fp);
		K++;
	}
	
	// N > K, sort K integers
	// N <= K, sort N integers.
	if(N > K)
		N = K;
	
	arr = (int*)malloc(sizeof(int)*N);
	fseek(fp,0,SEEK_SET);
	
	for(i = 0 ; i < N; i++){							
		fgets(str, sizeof(str), fp);
		arr[i] = atoi(str);
	}
	
	fclose(fp);					
	arr_tmp = (int*)malloc(sizeof(int)*N);
	
	// timer start
	start_time = clock();							
	do {
		// memory copy to record precise running time
		memcpy(arr_tmp, arr, sizeof(int)*N);
		counter++;
		MergeSort(arr_tmp, 0, N - 1);
	} while(clock() - start_time < 1000);
	
	// timer end & calculate time.
	Runtime = (double)(clock() - start_time) / (CLOCKS_PER_SEC/1000);
	Runtime = (double)Runtime / counter;
	
	// Print all array
	for(i=0 ; i < N ; i++){
		printf("%d\n", arr_tmp[i]);
	}

	printf("Running time : %lf ms\n", Runtime);
 	
	free(arr);
 	free(arr_tmp);
	return 0;
}

void MergeSort(int arr[], int left, int right){	
// Recursivly divide problem to two or more sub-problems
	int mid;

	if (left < right){
	
		mid = (left + right) / 2;

		// divide left sub-array 
		MergeSort(arr, left, mid);
		
		// divide right sub-array				
		MergeSort(arr, mid + 1, right);			
		
		// merge sub-arrays
		MergeTwoArea(arr, left, mid, right);	
	}

}

void MergeTwoArea(int arr[], int left, int mid, int right){
// merge two sub-arrays

	int left_Idx = left;
	int right_Idx = mid + 1;
	int i;

	// array for merge and sorted data
	int* sortArr = (int*)malloc(sizeof(int)*(right + 1));
	int sort_Idx = left;

	// merge left sub-array and right sub-array
	while (left_Idx <= mid && right_Idx <= right){
		if (arr[left_Idx] <= arr[right_Idx])
			sortArr[sort_Idx] = arr[right_Idx++];
		else
			sortArr[sort_Idx] = arr[left_Idx++];

		sort_Idx++;
	}
	
	// when left sub-array is all sorted. just link remaining right sub-array.
	if (left_Idx > mid){
		for (i = right_Idx; i <= right; i++)
			sortArr[sort_Idx++] = arr[i];
	}

	// when right sub-array is all sorted. just link remaining left sub-array.
	if (right_Idx > right){
		for (i = left_Idx; i <= mid; i++)
			sortArr[sort_Idx++] = arr[i];
	}
	
	// copy sorted data to arr
	for (i = left; i <= right; i++){		
		arr[i] = sortArr[i];
	}
	
	free(sortArr);
}
