/*
 * Marc Bolinas
 *
 * TA: Eeshita Biswas
 *
 * 9/27/17
 * LAB 3 PART 1
 *
 *
 *
 */



#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;




int *array_int_gen(int &length, int &high, int &low); //iteratively creates an array of length 25-50, sets high between 10-5 and low between -10 - -5

int *array_int_gen_rec(int &length, int &high, int &low); //recursively creates an array of length 25-50, sets high between 10-5 and low between -10 - -5

void fill_array(int *arr, int length, int high, int low); //fills given array with ints between low and high

void print_array(int *array, int size); //prints out the given array, new line every 10 ints

int hanning_window(int *array, int window_size); //applies a smoothing filter to given array, strength of smoothing determined by window_size

int *filter_array(int *array, int size, int window_size); //uses smoothing filter from hanning_window() to apply to the entire array

void print_array(int *array, int size, int high, int low); //graphically prints out array


int main(){
	srand(time(NULL));
	int high;
	int low;
	int length;
	int hanning_size = 3;

	int *pointer = array_int_gen_rec(length, high, low);

	cout << "Randomly generated array" << endl;
	print_array(pointer, length);

	cout << "Graph of above array" << endl;
	print_array(pointer, length, high, low);

	cout << endl << endl << endl;

	int *new_arr = filter_array(pointer, length, hanning_size);

	cout << "Filtered array" << endl;
	print_array(new_arr, length);

	cout << "Graph of the filtered array, hanning size " << hanning_size << endl;
	print_array(new_arr, length, high, low);

	return 0;
}




int *array_int_gen(int &length, int &high, int &low){
	length = (rand() % 25) + 25; //25-50
	high = (rand() % 5) + 5; //5-10
	low = (rand() % 5) - 10; //-10- -5
	int *arr = new int[length];

	for(int i = 0; i < length; i++){
		arr[i] = rand() % (high - low + 1) + low;
	}
	return arr;

}


int *array_int_gen_rec(int &length, int &high, int &low){
	length = (rand() % 25) + 25; //25-50
	high = (rand() % 5) + 5; //5-10
	low = (rand() % 5) - 10; //-10- -5
	int *arr = new int[length];

	fill_array(&arr[0], length, high, low);

	return arr;
}

void fill_array(int *arr, int length, int high, int low){
	if(length > 0){ //works by passing in the next element in the array as the first value. continue until reaching length
		arr[0] = rand() % (high - low + 1) + low;
		fill_array(&arr[1], length - 1, high, low);
	}
}


void print_array(int *array, int size){
	int count = 0;
	for(int i = 0; i < size; i++){

		if(array[i] < 0){ //I do this because the minus sign makes it take more space
			cout << array[i] << ", ";
		}
		else{
			cout << " " << array[i] << ", "; //prints an extra space so that everything stays lined up
		}

		count++;


		if(count == 10){
			cout << endl;
			count = 0;
		}
	}
	cout << endl;
}


int hanning_window(int *array, int window_size){
	int total_weight = 0;
	int weight = 1;
	int sum = 0;
	for(int i = 0 - (window_size / 2); i <= (window_size / 2); i++){ //array[0] is the center of the hanning window. go negative to get previous values
		sum += (array[i] * weight);
		total_weight += weight;
		if(i < 0){ //weight increases as it gets to the center, then decreases: 1,2,3,2,1
			weight++;
		}
		else{
			weight--;
		}
	}
	sum /= total_weight;

	return sum;
}


int *filter_array(int *array, int size, int window_size){
	int *new_arr = new int[size];

	int border = window_size / 2; //how many 0's to put at the start and end of the array because the hanning window won't work on those
	int index = 0;
	for(; index < border; index++){
		new_arr[index] = 0;
	}

	for(; index < size - border; index++){ //apply smoothing filter
		new_arr[index] = hanning_window(&array[index], window_size);
	}
	for(; index < size; index++){
		new_arr[index] = 0;
	}

	return new_arr;
}



void print_array(int *array, int size, int high, int low){
	for(; low <= high; low++){
		if(low < 0){ //again, this is so that the minus sign doesn't make things go out of alignment
			cout << low << ": ";
		}
		else{
			cout << " " << low << ": ";
		}


		for(int i = 0; i < size; i++){
			if(array[i] == low){
				cout << "x ";
			}
			else{
				cout << "  ";
			}
		}
		cout << endl;
	}
}
