#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;


void Merge(int theArray[], int first, int mid, int last, int* compareCount, int* movesCount){
	
}

void MergeSort(int theArray[], int first, int last, int* compareCount, int* movesCount){
	*compareCount++;
	if (first < last)
	{ // sort each half
		int mid = (first + last)/2; // index of midpoint
		// sort left half theArray[first..mid]
		MergeSort(theArray, first, mid, compareCount, movesCount);
		// sort right half theArray[mid+1..last]
		MergeSort(theArray, mid+1, last, compareCount, movesCount);
		// merge the two halves
		Merge(theArray, first, mid, last, compareCount, movesCount);
	} // end if
}

void GenerateRandomNumbers(int numbers[], int length){
	srand(time(NULL));
	for(int i = 0; i< length; i++){
		numbers[i] = (rand() % 999) + 1;
	}
}

void PrintData(int data[], int length){
	for(int i = 0; i < 100; i++){
		if(i%10 == 0){
			cout<<endl;
		}
		cout<<data[i]<<"\t";
	}
}

void OneHundredData(){
	int length;
	int data[100];
	
	cout<<"Generating Random Numbers....."<<endl;
	GenerateRandomNumbers(data, 100);
	PrintData(data, 100);	
}

void FiveHundredData(){
	
}

void OneThousandData(){
	
}

int main()
{
	OneHundredData();
    return 0;
}

