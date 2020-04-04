// Student ID : 20144320
// Student Name : Kim Gyeong-Hyeon

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class merge_sort {
	
	public static void mergeSort(int[] list, int length){	
	// Recursively divide problem to two or more sub-problems
		
		int mid = (length / 2);
		int leftSubList[] = new int[mid];
		int rightSubList[] = new int[length - mid];
		
		
		if (length == 1)
		return;
		
		// left sub-array
		for (int i = 0; i < mid; i++) {
			leftSubList[i] = list[i];
		}
		
		// right sub-array
		for (int i = 0; i < length - mid ; i++) {
			rightSubList[i] = list[mid + i];
		}
		
		// split left Sub-array
		mergeSort(leftSubList, leftSubList.length);
		// split right Sub-array
		mergeSort(rightSubList, rightSubList.length);
		
		// merge sub-arrays
		mergeTwoArea(leftSubList, rightSubList, list);
	}

	// merge two sub-arrays
	private static void mergeTwoArea(int[] leftSubList, int[] rightSubList, int[] list){
	
		int left = 0;
		int right = 0;
		int merge = 0;
	
		// merge two sub-arrays
		while(leftSubList.length != left && rightSubList.length != right) {
			if(leftSubList[left] > rightSubList[right]) {
				list[merge] = leftSubList[left];
				merge++;
				left++;
			} else {
				list[merge] = rightSubList[right];
				merge++;
				right++;
			}
		}
		
		// right sub array is done. put all left sub array as its turn
		while(leftSubList.length != left) {
			list[merge] = leftSubList[left];
			merge++;
			left++;
		}
		
		// left sub array is done. put all right sub array as its turn
		while(rightSubList.length != right) {
			list[merge] = rightSubList[right];
			merge++;
			right++;
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
			mergeSort(arr_temp, N);
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
