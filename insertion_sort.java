// Student ID : 20144320
// Student Name : Kim Gyeong-Hyeon

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class insertion_sort {

	public static void insertionSort(int[] list){
		
		int i, j, temp;
		
	  	for(i = 1; i < list.length; i++){
	  		
	  		j = i;
	  		temp = list[j];
	  		
	  		// compare arr[i] with neighboring arr[i-1]
	  		// if exchange values, go left and continue to compare
	  		while(--j >= 0 && temp > list[j]){
	  			
				list[j+1] = list[j];
				list[j] = temp;
			}
	  	}
	}

	
	public static void main(String[] args) {
		
		// check incorrect command line arguments
		if(args.length != 2) {
			System.out.println("incorrect command line arguments.");
			System.exit(-1);
		}
		
		int N = 0;
	
		try {
			N = Integer.parseInt(args[0]);
		} catch (Exception e) {
			// Check whether N is integer or not
			System.out.println("N is not integer.");
			System.exit(-1);
		}
		
		
		int count = 0;
		
		// args[1] is Filename
		File file = new File(args[1]);
		
		// count K (the number of integer in file)
		try {
			BufferedReader bufReader = new BufferedReader(new FileReader(file));
			String line = "";
			while((line = bufReader.readLine()) != null)
				count++;
			bufReader.close();
		} catch (Exception e) {
			System.out.println("File open error.");
		}
		
		// N > K, sort K integers.
		// N <= K, sort N integers.
		if(N > count)
			N = count;
		
		int[] arr, arr_temp;
		arr = new int[N];
		arr_temp = new int[N];
		
		// Save K number integer from file to arr
		try {
			Scanner scanner = new Scanner(file);
			for(int i = 0; i < N; i++) {
				arr[i] = Integer.parseInt(scanner.nextLine());
			}
		} catch (Exception e) {
			System.out.println("File open error.");
		}
		
		// counter for running time
		int counter = 0;
		long startTime = System.currentTimeMillis();
		
		do {
			System.arraycopy(arr, 0, arr_temp, 0, N);
			insertionSort(arr_temp);
			counter++;
		} while( (System.currentTimeMillis() - startTime) < 1000 );
		// Running time < 1000ms, Run several times for precise value.
		
		float runningTime = (float)(System.currentTimeMillis() - startTime) / counter;
	
		// print sorted array
		for(int i = 0; i < N; i++) {
			System.out.println(arr_temp[i]);
		}
		// running time
		System.out.println("running time : " + runningTime + " ms");
		
	}
}
