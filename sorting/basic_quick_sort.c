/**
 * "Quick Sort"
 * - ./basic_quick_sort <input_file_name> <N>
 * - measure running time of 'Quick Sort'
 *
 * 
 * https://github.com/ddamddi
  **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

// Swap x and y
#define SWAP(X,Y,t)  { (t)=(X); (X)=(Y); (Y)=(t); }


void choose_pivot (int *data, unsigned int n) {
	
	int randNum, tmp;
	
	// Randomly choose pivot index  between 0 ~ n-1
	randNum = rand() % n;
	
	// Place pivot at first elements of array
	SWAP(data[0], data[randNum], tmp)
}

unsigned long quick_sort (int *data, unsigned int n) {
    	unsigned long cnt = (n - 1); // number of comparison
    
	int i = 1, j = 1;
	int k, tmp;
	
	
	if(n <= 1)
		return -1;
	
	// choose pivot and  always place it at first element of array
    	choose_pivot(data, n);
    
    	for(k = 0; k < n-1; k++) {
    	
    		// pivot (= data[0]) > arr[j] --> SWAP(arr[i], arr[j]) && increment i
    		if(data[0] > data[j]) {
    			SWAP(data[i], data[j], tmp);
    			i++;   		
		}
		// pivot <= arr[j] --> increment j
		j++;
	}
	
	// Move pivot to center
	SWAP(data[0], data[i - 1], tmp);
	
	// sorting array with element which is smaller than pivot
	quick_sort(data, i-1);
	// sorting array with element which is larger than pivot
	quick_sort((data + i), j - i);
	
	return cnt;
}

int main (int argc, char* argv[]) {
	
	int i, N, K = 0;
	int counter = 0;
	int * arr, * arr_tmp;	// array for memcpy
	double duration;
	clock_t start_time;
	char str[20];
	
	// Check command line arguments.
	// ex) <your_program> <input_file> <N> : argc = 3
	if(argc != 3) {
		printf("incorrect command line error\n");
		return -1;
	}

	FILE * fp = fopen(argv[1] ,"rt");
	
	// Check file is open error.
	if(fp == NULL) {
		printf("File open Error\n");
		return -1;
	}
	
	// Change string N to integer N
	N = (int)strtol(argv[2], NULL, 10);
	
	// Count K (number of integer in file)
	while(!feof(fp)) {
		fgets(str, sizeof(str), fp);
		K++;
	}
	
	// N > K, sort K integers
	// N <= K, sort N integers.
	if(N > K)
		N = K;
	
	arr = (int*)malloc(sizeof(int)* N);
	fseek(fp,0,SEEK_SET);
	
	for(i = 0 ; i < N; i++) {
		fgets(str,sizeof(str),fp);
		arr[i] = (int)strtol(str, NULL, 10);
	}
	
	fclose(fp);
	arr_tmp = (int*)malloc(sizeof(int)*N);

	// Set seed for random pivot
	srand((unsigned int)time(NULL));
	
	// timer start
	start_time = clock();
	do {
		// memory copy to record precise running time
		memcpy(arr_tmp, arr, sizeof(int)*N);
		counter++;
		quick_sort(arr_tmp, N);
	} while(clock() - start_time < 1000);

	// timer end & calculate time.
	duration = (double)(clock() - start_time) / (CLOCKS_PER_SEC / 1000);
	duration = duration / counter;

	// Print all elements in sorted array 
	for(i = 0; i < N; i++) {
		printf("%d\n", arr_tmp[i]);
	}
		
	// Please keep these printf statements!
	printf("N = %7d,\tRunning_Time = %.3f ms\n", N, duration);	
	
	free(arr);
	free(arr_tmp);
   	return 0;
}

