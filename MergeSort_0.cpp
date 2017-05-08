#include<iostream>
#include<cstdlib>
#include<time.h>
#include<conio.h>
using namespace std;

void PrintData(int data[], int length){
	cout<<endl<<endl;
	for(int i = 0; i < length; i++){
		
		if(i%10 == 0){
			cout<<endl;
		}
		else{ 
			cout<<"\t";
		}
		
		cout<<data[i];
	}
	cout<<endl<<endl;
}

void CopyArray(int array1[], int array2[], int length){
	for(int i=0; i < length; i++){
		array2[i] = array1[i];	
	}	
}

void Merge(int theArray[], int length, int first, int mid, int last, int* compareCount, int* movesCount){
	int tempArray[length]; // temp array
	int first1 = first; // subarray begin
	int last1 = mid; // end of first subarray
	int first2 = mid + 1; // secnd subarry begin
	int last2 = last; // end of secnd subarry
	int index = first1;
	
	// next available location in tempArray
	for (; (first1 <= last1) && (first2 <= last2); ++index){
		*compareCount += 1;
		if (theArray[first1] < theArray[first2]){
			tempArray[index] = theArray[first1];
			++first1;
			*movesCount += 1;	
		}
		else {
			tempArray[index] = theArray[first2];
			++first2;
			*movesCount += 1;
		}
	}
	
	for (; first1 <= last1; ++first1, ++index){
		tempArray[index] = theArray[first1];
		*movesCount += 1;
	}
		
	for (; first2 <= last2; ++first2, ++index){
		tempArray[index] = theArray[first2];
		*movesCount += 1;
	}

	for (index = first; index <= last; ++index)
		theArray[index] = tempArray[index];
}

void MergeSort(int theArray[], int length, int first, int last, int* divideCount, int* compareCount, int* movesCount){
	
	if (first < last)
	{ // sort each half
		*divideCount += 1;
		int mid = (first + last)/2; // index of midpoint
		// sort left half theArray[first..mid]
		MergeSort(theArray, length, first, mid, divideCount, compareCount, movesCount);
		// sort right half theArray[mid+1..last]
		MergeSort(theArray, length, mid+1, last, divideCount, compareCount, movesCount);
		// merge the two halves
		Merge(theArray, length, first, mid, last, compareCount, movesCount);
	} // end if
}

int Partition(int T[], int first, int last, int* compareCount, int* movesCount)
{
     int pivot, temp;
     int loop, cutPoint, bottom, top;
     pivot = T[first];
     bottom = first;
     top = last;
     loop = 1;
     while (loop){
		while (T[top]>pivot)
		{
            *compareCount+=1;
		   	top--;
		}
         //  cout<<"top"<<T[top]<<endl;
        while (T[bottom]<pivot)
        { 
			*compareCount+=1;
		   	bottom++;
		}
        //   cout<<"bottom"<<T[bottom]<<endl;
	     if (bottom < top)
		 {
				
           if(T[top] == pivot && T[bottom]== pivot){
				*compareCount+=1;
				top--;
			}
	           temp = T[bottom];
	           T[bottom]=T[top];
	           T[top]=temp;
	           *movesCount+=1;
	    }
	     else {
	          loop=0;
	          cutPoint=top;
	    }
     }
     //cout<<"cutpoint"<<cutPoint<<endl;
     return cutPoint;
} //end partition()

void QuickSort (int T[], int first, int last, int* compareCount, int* movesCount)
{
     int cut;
     if (first < last){
          //cout<<"check0"<<endl;
          cut = Partition(T,first,last, compareCount, movesCount);
          //PrintData(T, 12);
         // getch();
          //cout<<"check1"<<endl;
          QuickSort(T, first, cut, compareCount, movesCount);
          //cout<<"check2"<<endl;
          QuickSort(T, cut+1, last, compareCount, movesCount);
          //cout<<"check3"<<endl;
          
     }
}

void GenerateRandomNumbers(int numbers[], int length){
	srand(time(NULL));
	for(int i = 0; i< length; i++){
		numbers[i] = (rand() % 999) + 1;
	}
}

void OneHundredData(int counts[]){
	int length = 100;
	int data[length];
	//int data[] = {749, 437, 730, 935, 987, 826, 121, 414, 979, 238, 5, 5};
	int tempdata[length];
	int divCount, comCount, movCount;
	divCount = 0;
	comCount = 0;
	movCount = 0;
	//cutPoint = 0;
	
	cout<<"Generating Random Numbers....."<<endl;
	GenerateRandomNumbers(data, length);
	CopyArray(data, tempdata, length);
	PrintData(data, length);	
	cout<<endl<<"Sorting...Merge";
	MergeSort(data, length, 0, length - 1, &counts[0], &counts[1],&counts[2]);
	PrintData(data, length);
	
	//cout<<endl<<endl<<"Division count: "<<divCount<<endl;
	//cout<<"Compare count: "<<comCount<<endl;
	//cout<<"Moves count: "<<movCount<<endl;
	
	//CopyArray(data, tempdata, length);
	cout<<"Original Data";
	PrintData(tempdata, length);
	cout<<endl<<"Sorting...Quick"<<endl<<endl;
    QuickSort(tempdata, 0, length - 1, &counts[3], &counts[4]);
	PrintData(tempdata, length);
}

void FiveHundredData(){
	
}

void OneThousandData(){
	
}

int main()
{
//	int nums[50];
//	GenerateRandomNumbers(nums, 50);
//	PrintData(nums, 100);
	int Data100[]={0,0,0,0,0};
	int Data500[]={0,0,0,0,0};
	int Data1000[]={0,0,0,0,0};
	
	OneHundredData(Data100);
	cout<<endl<<endl;
	cout<<"\t\tMerge Sort\tQuick Sort"<<endl;
	cout<<"Compare\t\t"<<Data100[1]<<"\t\t"<<Data100[3]<<endl;
	cout<<"Moves\t\t"<<Data100[2]<<"\t\t"<<Data100[4]<<endl;

	getch();
    return 0;
}

