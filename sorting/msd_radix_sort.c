// MSD Radix Sort
// https://github.com/ddamddi

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

// Macro for bit shifting / the Range is CHAR_BIT = 8bit => 256
#define digit(A ,i) ( ( A ) >> ( ( i ) * CHAR_BIT ) & UCHAR_MAX )

void sort(unsigned int a[], unsigned int aux[], int first, int last, int d) {
    
	// if subarray have one or no element, stop key indexed counting and recursive call.
	if(last <= first) return;

		// key indexed counting
        unsigned int i, count[UCHAR_MAX + 2] = {0}; 
         
        for(i = first; i <= last; i++) {
            count[digit(a[i], d) + 1]++;
    	} 

        for(i = 0; i < UCHAR_MAX; i++) {    
            count[i + 1] += count[i];
    	}
		 
        for(i = first; i <= last; i++){ 
            aux[count[digit(a[i], d)]++] = a[i];
    	} 
        
        for(i = first; i <= last; i++){ 
            a[i] = aux[i - first];
		}
        
		// sort R(=256) subarrays recursively
        sort(a, aux, first, first + count[0] - 1, d - 1);
        
        for(i = 0; i < UCHAR_MAX ; i++) {
            sort(a, aux, first + count[i], first + count[i + 1] - 1, d - 1);
      	}   
         
}

void MSD_radix_sort(unsigned int a[], int first, int last) {
	
    int d = sizeof(int) - 1;
    unsigned int* aux = (unsigned int*) malloc((last - first + 1) * sizeof(unsigned int));
    
    sort(a, aux, first, last, d);    
     
    free(aux);
}

int main(int argc, char* argv[]) {
	
	int i, N, K = 0;
	int counter = 0;
	unsigned int * arr, * arr_tmp;	// array for memcpy
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
	N = (unsigned int)strtol(argv[2], NULL, 10);
	
	// Count K (number of integer in file)
	while(!feof(fp)) {
		fscanf(fp, "%s\n", str);
		if(str != "\0")
			K++;
	}
	
	// N > K, sort K integers.
	// N <= K, sort N integers.
	if(N > K)
		N = K;
	
	arr = (unsigned int*)malloc(sizeof(unsigned int)* N);
	fseek(fp, 0, SEEK_SET);
	
	for(i = 0 ; i < N; i++) {
		fgets(str, sizeof(str), fp);
		arr[i] = (unsigned int)strtol(str, NULL, 10);
	}
	
	fclose(fp);
	arr_tmp = (unsigned int*)malloc(sizeof(unsigned int) * N);

	// Set seed for random pivot
	srand((unsigned int)time(NULL));
	
	// timer start
	start_time = clock();
	do {
		// memory copy to record precise running time
		memcpy(arr_tmp, arr, sizeof(int)*N);
		counter++;
		MSD_radix_sort(arr_tmp, 0, N-1);
		
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
